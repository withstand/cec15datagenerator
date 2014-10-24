
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