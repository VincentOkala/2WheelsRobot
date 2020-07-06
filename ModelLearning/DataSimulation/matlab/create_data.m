function y = create_data(n_samples, filename)
    fID = fopen(filename, 'w+');

    formatSpec = '%1.4f, %1.4f, %1.4f, %1.4f, %1.4f, %1.4f, %1.4f, %1.4f\n';
    gx = zeros(n_samples,1);
    gy = zeros(n_samples,1);
    gz = zeros(n_samples,1);
    ax = zeros(n_samples,1);
    ay = zeros(n_samples,1);
    az = zeros(n_samples,1);
    c1 = zeros(n_samples,1);
    c2 = zeros(n_samples,1);
    for i=2:n_samples
        c1(i,1) = sin(0.01*i);
        c2(i,1) = sin(0.05*i);
        gx(i,1) = 10*(0.5 - 1*gx(i-1,1) +  7*c1(i-1,1) +    gy(i-1,1) + gz(i-1,1) + c2(i-1,1) )/(4 + 7^2);
        gy(i,1) = 10*(0.5 + 2*gx(i-1,1) -  8*c1(i-1,1) +    gy(i-1,1) + gz(i-1,1) + c2(i-1,1) )/(3+2^2+8^2);
        gz(i,1) = 10*(0.5 + 3*gx(i-1,1) +  9*c1(i-1,1) -    gy(i-1,1) + gz(i-1,1) + c2(i-1,1) )/(3+3^2+9^2);
        ax(i,1) = 10*(0.5 + 4*ax(i-1,1) + 10*c1(i-1,1) + 15*ay(i-1,1) - az(i-1,1) + c2(i-1,1)) /(2+4^2+10^2+15^2);
        ay(i,1) = 10*(0.5 + 5*ax(i-1,1) + 11*c1(i-1,1) + 17*ay(i-1,1) + az(i-1,1) - c2(i-1,1)) /(2+15^2+11^2+5^2);
        az(i,1) = 10*(0.5 + 6*ax(i-1,1) - 12*c1(i-1,1) + 19*ay(i-1,1) + az(i-1,1) + c2(i-1,1)) /(2+19^2+12^2+6^2) ;      
        
        fprintf(fID, formatSpec, gx(i,1), gy(i,1), gz(i,1), ax(i,1), ay(i,1), az(i,1), c1(i,1), c2(i,1));
    end
    fclose(fID);
    y = 0;
end