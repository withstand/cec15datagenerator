function q = cec15rotate(n)
% [q,~] = qr(cec15rand(n,n));
% if det(q)<0
%     q(:,end) = -q(:,end);
% end
q = my_orth(cec15rand(n,n));

if cec15rand()>0.5
    i = cec15uniform(n);
    q(i,:) = q(i,:) * 2;
end


end



function u = my_orth(A)
u = zeros(size(A));
% classic Gram-Schmidt
% for i = 1:size(A,1)
%     u(i,:) = A(i,:);
%     for j = 1:i-1
%         u(i,:) = u(i,:) - proj(u(j,:), A(i,:));
%     end
% end

% MGS
for i = 1:size(A,1)
    u(i,:) = A(i,:);
    for j = 1:i-1
        u(i,:) = u(i,:) - proj(u(j,:), u(i,:));
    end
    u(i,:) = u(i,:) / mynorm(u(i,:));
end



    function n = mynorm(u)
        sum = 0;
        for ii=1:numel(u)
            sum = sum + u(ii) * u(ii);
        end
        n = sqrt(sum);
    end
    function p = proj(u,v)
        p = inner(u,v) / inner(u,u) * u;
    end
    function sum = inner(u,v)
        sum = 0;
        for ii=1:numel(u)
            sum = sum + u(ii) * v(ii);
        end
    end

end