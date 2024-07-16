enum ScheduleType { static_t, global_t, local_t,  local_32_t };
#include <iostream>
#include <iomanip>
#include <fstream> 
void check_results(float *result, int size, int* mult, ScheduleType t) {
        std::string filename;

    // Determine the filename based on the ScheduleType
    switch (t) {
        case static_t:
            filename = "static.txt";
            break;
        case global_t:
            filename = "global.txt";
            break;
        case local_t:
            filename = "local.txt";
            break;
        case local_32_t:
            filename = "local_32.txt";
            break;
        default:
            // Handle unknown ScheduleType or provide a default filename
            std::cerr << "Unknown ScheduleType" << std::endl;
            return;
    }

    // Open the file for writing
    std::ofstream outputFile(filename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write the data to the file
    for (int i = 0; i < size; ++i) {
        outputFile << std::setprecision(6) << result[i] << " " << mult[i] << std::endl;
    }

    // Close the file
    outputFile.close();

    std::cout << "Data written to " << filename << std::endl;
}

void check_timing(double seconds, ScheduleType t) {

}
