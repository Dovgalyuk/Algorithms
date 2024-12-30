f (!(file >> a >> b)) {
        std::cout << "Error reading from file\n";
        file.close();
        return 1;