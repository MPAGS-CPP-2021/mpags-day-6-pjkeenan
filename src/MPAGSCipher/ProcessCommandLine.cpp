#include "ProcessCommandLine.hpp"

#include <iostream>
#include <string>
#include <vector>

void processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        ProgramSettings& settings)
{
    // // Status flag to indicate whether or not the parsing was successful
    // bool processStatus{true};

    // Process the arguments - ignore zeroth element, as we know this to be
    // the program name and don't need to worry about it
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            // Set the indicator and terminate the loop
            settings.helpRequested = true;
            break;
        } else if (cmdLineArgs[i] == "--version") {
            // Set the indicator and terminate the loop
            settings.versionRequested = true;
            break;
        } else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                // Throw an exception for the missing argument
                throw MissingArgument("-i needs a filename argument");
            } else {
                // Got filename, so assign value and advance past it
                settings.inputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                // Throw an exception for the missing argument
                throw MissingArgument("-o needs a filename argument");
            } else {
                // Got filename, so assign value and advance past it
                settings.outputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-k") {
            // Handle cipher key option
            // Next element is the key unless -k is the last argument
            if (i == nCmdLineArgs - 1) {
                // Throw an exception for the missing argument
                throw MissingArgument("-k needs a filename argument");
            } else {
                // Got the key, so assign the value and advance past it
                settings.cipherKey = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "--encrypt") {
            settings.cipherMode = CipherMode::Encrypt;
        } else if (cmdLineArgs[i] == "--decrypt") {
            settings.cipherMode = CipherMode::Decrypt;
        } else if (cmdLineArgs[i] == "-c") {
            // Handle cipher type option
            // Next element is the name of the cipher, unless -c is the last argument
            if (i == nCmdLineArgs - 1) {
                // Throw an exception for the missing argument
                throw MissingArgument("-c needs a filename argument");
            } else {
                // Got the cipher name, so assign the value and advance past it
                if (cmdLineArgs[i + 1] == "caesar") {
                    settings.cipherType = CipherType::Caesar;
                } else if (cmdLineArgs[i + 1] == "playfair") {
                    settings.cipherType = CipherType::Playfair;
                } else if (cmdLineArgs[i + 1] == "vigenere") {
                    settings.cipherType = CipherType::Vigenere;
                } else {
                    // Throw an exception for the unknown argument
                    throw UnknownArgument("Unknown cipher type'" + cmdLineArgs[i + 1] + "'");
                }
                ++i;
            }
        } else {
            // Have encoutered an unknown flag -> throw exception
            throw UnknownArgument("unknown argument '" + cmdLineArgs[i] + "'");
        }
    }
}