%To run: plotBER('berResult file name', num of rows in berResult file)

% Input Param:
%   filename-Path to the 'swrcGP_Hamming.berResult' uploaded to Matlab
%   online
%
%   num_of_rows - Up to which row of data you wanna plot
function plotBER(filename, num_of_rows)
    data = importdata(filename, '\t', num_of_rows);
    BER_referData = csvread('./InputData/BER_simulated_slide.csv');
    FER_referData = csvread('./InputData/FER_simulated_slide.csv');
   
    % Processing for Header Row
    header_row = erase(data{1}, '#');  % Remove the hashtag from header row
    header = split(deblank(string(header_row)));   % Convert from Char to String type, then remove the whitespace from ends of string, then split into individual column names
    header(header == "") = []; % Remove empty column names

    % Find the Header Column Index
    SNR_col = find(header=="SNR"); 
    BER_col = find(header=="BER"); 
    FER_col = find(header=="FER"); 
    
    % Processing the data points
    SNR = [];
    BER = [];
    FER = [];
    for i = 2:num_of_rows
        data_row = sscanf(data{i},'%f'); % Split each row into individual data
        
        % Append data points
        SNR = [SNR, data_row(SNR_col)]
        BER = [BER, data_row(BER_col)]
        FER = [FER, data_row(FER_col)]
    end

    % Sort the data points based on the SNR order
    [SNRsorted, I] = sort(SNR)
    BERsorted = BER(I)
    FERsorted = FER(I)

    % Plot BER
    figure
    semilogy(SNRsorted, BERsorted, 'r-x'), grid on
    %hold on
    %semilogy(BER_referData(:, 1), BER_referData(:, 2), 'g-x')
    title('BER vs SNR')
    xlabel('SNR (dB)')
    ylabel('Log 10 BER')
    %legend('Simulated','Reference')

    % Plot FER 
    figure
    semilogy(SNRsorted, FERsorted, 'b-x'), grid on
    %hold on
    %semilogy(FER_referData(:, 1), FER_referData(:, 2), 'g-x')
    title('FER vs SNR')
    xlabel('SNR (dB)')
    ylabel('Log 10 FER')
    %legend('Simulated', 'Reference')
end