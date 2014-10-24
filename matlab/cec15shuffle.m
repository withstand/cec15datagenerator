function permutation = cec15shuffle(n)

permutation = zeros(1,n);
for i = 1:n
    j = cec15uniform(i);
    permutation(i) = permutation(j);
    permutation(j) = i;
end


end