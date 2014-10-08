
/**************************************************************************
**
** Copyright (C) 1993 David E. Steward & Zbigniew Leyk, all rights reserved.
**
**			     Meschach Library
** 
** This Meschach Library is provided "as is" without any express 
** or implied warranty of any kind with respect to this software. 
** In particular the authors shall not be liable for any direct, 
** indirect, special, incidental or consequential damages arising 
** in any way from use of the software.
** 
** Everyone is granted permission to copy, modify and redistribute this
** Meschach Library, provided:
**  1.  All copies contain this copyright notice.
**  2.  All modified copies shall carry a notice stating who
**      made the last modification and the date of such modification.
**  3.  No charge is made for this software or works derived from it.  
**      This clause shall not be construed as constraining other software
**      distributed on the same medium as this software, nor is a
**      distribution fee considered a charge.
**
***************************************************************************/


/*
  This file contains the routines needed to perform QR factorisation
  of matrices, as well as Householder transformations.
  The internal "factored form" of a matrix A is not quite standard.
  The diagonal of A is replaced by the diagonal of R -- not by the 1st non-zero
  entries of the Householder vectors. The 1st non-zero entries are held in
  the diag parameter of QRfactor(). The reason for this non-standard
  representation is that it enables direct use of the Usolve() function
  rather than requiring that  a seperate function be written just for this case.
  See, e.g., QRsolve() below for more details.
  
*/


static	char	rcsid[] = "$Id: qrfactor.c,v 1.5 1994/01/13 05:35:07 des Exp $";

#include	<stdio.h>
#include	<math.h>
#include        "matrix2.h"





#define		sign(x)	((x) > 0.0 ? 1 : ((x) < 0.0 ? -1 : 0 ))

extern	VEC	*Usolve();	/* See matrix2.h */

/* Note: The usual representation of a Householder transformation is taken
   to be:
   P = I - beta.u.uT
   where beta = 2/(uT.u) and u is called the Householder vector
   */

/* QRfactor -- forms the QR factorisation of A -- factorisation stored in
   compact form as described above ( not quite standard format ) */
#ifndef ANSI_C
MAT	*QRfactor(A,diag)
MAT	*A;
VEC	*diag;
#else
MAT	*QRfactor(MAT *A, VEC *diag)
#endif
{
    unsigned int	k,limit;
    Real	beta;
    STATIC	VEC	*hh=VNULL, *w=VNULL;
    
    if ( ! A || ! diag )
	error(E_NULL,"QRfactor");
    limit = min(A->m,A->n);
    if ( diag->dim < limit )
	error(E_SIZES,"QRfactor");
    
    hh = v_resize(hh,A->m);
    w  = v_resize(w, A->n);
    MEM_STAT_REG(hh,TYPE_VEC);
    MEM_STAT_REG(w, TYPE_VEC);
    
    for ( k=0; k<limit; k++ )
    {
	/* get H/holder vector for the k-th column */
	get_col(A,k,hh);
	/* hhvec(hh,k,&beta->ve[k],hh,&A->me[k][k]); */
	hhvec(hh,k,&beta,hh,&A->me[k][k]);
	diag->ve[k] = hh->ve[k];
	
	/* apply H/holder vector to remaining columns */
	/* hhtrcols(A,k,k+1,hh,beta->ve[k]); */
	_hhtrcols(A,k,k+1,hh,beta,w);
    }

#ifdef	THREADSAFE
    V_FREE(hh);	V_FREE(w);
#endif

    return (A);
}



/* makeQ -- constructs orthogonal matrix from Householder vectors stored in
   compact QR form */
#ifndef ANSI_C
MAT	*makeQ(QR,diag,Qout)
MAT	*QR,*Qout;
VEC	*diag;
#else
MAT	*makeQ(const MAT *QR,const VEC *diag, MAT *Qout)
#endif
{
    STATIC	VEC	*tmp1=VNULL,*tmp2=VNULL;
    unsigned int	i, limit;
    Real	beta, r_ii, tmp_val;
    int	j;
    
    limit = min(QR->m,QR->n);
    if ( ! QR || ! diag )
	error(E_NULL,"makeQ");
    if ( diag->dim < limit )
	error(E_SIZES,"makeQ");
    if ( Qout==(MAT *)NULL || Qout->m < QR->m || Qout->n < QR->m )
	Qout = m_get(QR->m,QR->m);
    
    tmp1 = v_resize(tmp1,QR->m);	/* contains basis vec & columns of Q */
    tmp2 = v_resize(tmp2,QR->m);	/* contains H/holder vectors */
    MEM_STAT_REG(tmp1,TYPE_VEC);
    MEM_STAT_REG(tmp2,TYPE_VEC);
    
    for ( i=0; i<QR->m ; i++ )
    {	/* get i-th column of Q */
	/* set up tmp1 as i-th basis vector */
	for ( j=0; j<QR->m ; j++ )
	    tmp1->ve[j] = 0.0;
	tmp1->ve[i] = 1.0;
	
	/* apply H/h transforms in reverse order */
	for ( j=limit-1; j>=0; j-- )
	{
	    get_col(QR,j,tmp2);
	    r_ii = fabs(tmp2->ve[j]);
	    tmp2->ve[j] = diag->ve[j];
	    tmp_val = (r_ii*fabs(diag->ve[j]));
	    beta = ( tmp_val == 0.0 ) ? 0.0 : 1.0/tmp_val;
	    /* hhtrvec(tmp2,beta->ve[j],j,tmp1,tmp1); */
	    hhtrvec(tmp2,beta,j,tmp1,tmp1);
	}
	
	/* insert into Q */
	set_col(Qout,i,tmp1);
    }

#ifdef	THREADSAFE
    V_FREE(tmp1);	V_FREE(tmp2);
#endif

    return (Qout);
}

