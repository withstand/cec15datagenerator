% datafile generation for 
%  CEC15 SS04: Bound Constrained Single-Objective Numerical Optimization Competition - Expensive part
cec15reseed([12345, 67890, 98765, 43210]);
cf_numbers = [ones(1, 12), 5, 3, 5];
for func_num = 1:15
    for dim = [10,30]
        Mfile = ['M_' num2str(func_num) '_D' num2str(dim) '.txt'];
        Sfile = ['shift_data_' num2str(func_num) '_D' num2str(dim) '.txt'];
        Permfile = ['shuffle_data_' num2str(func_num) '_D' num2str(dim) '.txt'];
        Mdata = zeros(dim*cf_numbers(func_num), dim);
        for i = 1:cf_numbers(func_num)
            Mdata((i-1)*dim+1:i*dim,:) = cec15rotate(dim);            
        end
        Sdata = zeros(cf_numbers(func_num) * dim, 1);
        for i = 1:cf_numbers(func_num)
            % to [-80,80]
            Sdata((i-1)*dim+1:i*dim) = -80 + 160 * cec15rand(dim,1);            
        end
        PermData = cec15shuffle(dim);
                

        fid = fopen(Mfile,'w');
        for i=1:size(Mdata,1)
            fprintf('%24.6e ', Mdata(i,:));
            fprintf('\n');
        end
        fclose(fid);
        
        fid = fopen(Sfile,'w');
        fprintf('%24.6e ', Sdata);
        fprintf('\n');
        fclose(fid);
        

        % save(Mfile,'Mdata','-ascii');        
        % save(Sfile,'Sdata','-ascii');
        
        fid = fopen(Permfile,'w');
        fprintf(fid,'%d\t', PermData);
        fclose(fid);
        
    end
end