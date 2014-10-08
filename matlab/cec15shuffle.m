function permutation = cec15shuffle(n)

permutation = zeros(1,n);
for i = 1:n
    j = cec15uniform(i);
    permutation(i) = permutation(j);
    permutation(j) = i;
end


    function ret = cec15uniform(m, row, col)
        if nargin==1
            row = 1;
            col = 1;
        end
        if nargin ==2
            col = row;
        end      
        
        ret = ceil(cec15rand(row,col) * m);
        
    end
end