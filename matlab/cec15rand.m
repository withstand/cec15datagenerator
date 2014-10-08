function ret = cec15rand(n,m)
if nargin == 0
    m = 1;
    n = 1;
end
if nargin < 2
    m = n;
end

ret = zeros(n,m);
for i=1:n
    for j = 1:m
        ret(i,j) = jkiss();
    end
end

end