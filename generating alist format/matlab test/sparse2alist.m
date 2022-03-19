%Code is from xiaoshaoning
%<https://github.com/xiaoshaoning/5g-ldpc/blob/master/alist_generate.m>


load H_matrix.txt
H = H_matrix;

[N, M] = size(H);

fid = fopen('NR_ldpc.alist', 'w');
fprintf(fid, '%d %d\n', N, M);

%H = full(H);

row_non_zero_entry_number = sum(H, 2).';
column_non_zero_entry_number = sum(H, 1);

fprintf(fid, '%d %d\n', max(row_non_zero_entry_number), max(column_non_zero_entry_number));

for index = 1:N
  fprintf(fid, '%d ', row_non_zero_entry_number(index));
end

fprintf(fid, '\n');

for index = 1:M
  fprintf(fid, '%d ', column_non_zero_entry_number(index));
end

fprintf(fid, '\n');

%put in column index of non zero elements in each row
for row_index = 1:N
  non_zero_entry_positions = find(H(row_index, :) ~= 0);
  %find(H(row_index, :) ~= 0)
  max(row_non_zero_entry_number)

  for index = 1:max(row_non_zero_entry_number) % length(non_zero_entry_positions)
    if index <= length(non_zero_entry_positions)
        %non_zero_entry_positions(index)
      fprintf(fid, '%d ', non_zero_entry_positions(index));
    else
      fprintf(fid, '0 ');
    end
  end

  fprintf(fid, '\n');
end

for column_index = 1:M
  non_zero_entry_positions = find(H(:, column_index) ~= 0);

  for index = 1:max(column_non_zero_entry_number)
    if index <= length(non_zero_entry_positions)
      fprintf(fid, '%d ', non_zero_entry_positions(index));
    else
      fprintf(fid, '0 ');    
    end
  end

  fprintf(fid, '\n');
end

fclose(fid);

