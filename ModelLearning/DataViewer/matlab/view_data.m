function view_data(filename)
    fID = fopen(filename, 'r');
    error = 0;
    while(error == -1)
        error = FGETL(fID);
        
    end
end