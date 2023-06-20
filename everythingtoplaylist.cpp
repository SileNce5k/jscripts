//chatgpt wrote all of this code.
//This program is used to modify "export" from everything (https://www.voidtools.com/) to a format that vlc can handle.

#include <iostream>
#include <fstream>
#include <regex>

std::string removeFirstLine(const std::string& input) {
    size_t pos = input.find_first_of('\n');
    if (pos != std::string::npos)
        return input.substr(pos + 1);
    else
        return "";
}

std::string removeQuotationMarks(const std::string& input) {
    std::string output = input;
    output.erase(std::remove(output.begin(), output.end(), '\"'), output.end());
    return output;
}

std::string runRegexPattern(const std::string& input) {
    std::regex pattern(",(?:(?!X).)+");
    return std::regex_replace(input, pattern, "");
}

std::string getOutputFileName(const std::string& inputFile) {
    size_t pos = inputFile.find_last_of('.');
    std::string extension = inputFile.substr(pos);
    std::string baseName = inputFile.substr(0, pos);
    return baseName + "_modified" + extension;
}

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}
bool promptOverwrite() {
    std::string input;
    std::cout << "A file with the modified name already exists. Do you want to overwrite it? (y/n): ";
    std::cin >> input;
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return (input == "y");
}


void processFile(const std::string& inputFile) {
    // Read input file
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << inputFile << std::endl;
        return;
    }

    std::cout << "Reading input file: " << inputFile << std::endl;

    std::string input((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
    file.close();

    // Remove first line
    std::cout << "Removing the first line..." << std::endl;
    std::string output = removeFirstLine(input);

    // Remove quotation marks
    std::cout << "Removing quotation marks..." << std::endl;
    output = removeQuotationMarks(output);

    // Run regex pattern
    std::cout << "Applying regex pattern..." << std::endl;
    output = runRegexPattern(output);

    // Generate output file name
    std::string outputFile = getOutputFileName(inputFile);

    // Check if output file already exists
    if (fileExists(outputFile)) {
        bool overwrite = promptOverwrite();
        if (!overwrite) {
            std::cout << "Operation canceled. No files modified." << std::endl;
            return;
        }
    }

    // Write output file
    std::ofstream outputFileStream(outputFile);
    if (!outputFileStream.is_open()) {
        std::cout << "Failed to create output file: " << outputFile << std::endl;
        return;
    }

    std::cout << "Writing output file: " << outputFile << std::endl;

    outputFileStream << output;
    outputFileStream.close();

    std::cout << "Modified file created: " << outputFile << std::endl;
}


void displayHelp() {
    std::cout << "Usage: program [input_file]" << std::endl;
    std::cout << std::endl;
    std::cout << "This program removes the first line, replaces quotation marks, and applies a regex pattern to the input file." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        displayHelp();
        return 0;
    }

        std::string argument = argv[1];
        if (argument == "--help" || argument == "-h") {
        displayHelp();
        return 0;
    }

    std::string inputFile = argv[1];
    processFile(inputFile);

    return 0;
}
