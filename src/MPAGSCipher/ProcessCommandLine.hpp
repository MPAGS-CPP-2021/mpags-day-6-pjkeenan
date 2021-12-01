#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include "CipherMode.hpp"
#include "CipherType.hpp"

#include <string>
#include <vector>
#include <stdexcept>

/**
 * \file ProcessCommandLine.hpp
 * \brief Contains the declarations of the data structures and functions associated with the processing of command-line arguments
 */

/**
 * \struct ProgramSettings
 * \brief Holds the settings of the program that can be modified by command-line arguments
 */
struct ProgramSettings {
    /// Indicates the presence of the help flag in the arguments
    bool helpRequested;
    /// Indicates the presence of the version flag in the arguments
    bool versionRequested;
    /// Name of the input file
    std::string inputFile;
    /// Name of the output file
    std::string outputFile;
    /// Key to be used in encrypting/decrypting routine
    std::string cipherKey;
    /// Flag indicating the mode in which the cipher should run (i.e. encrypt or decrypt)
    CipherMode cipherMode;
    /// Flag indicating which cipher to use (e.g. Caesar, Playfair, etc.)
    CipherType cipherType;
};

/**
 * \brief Processes the command-line arguments and modifies accordingly the program settings
 *
 * \param cmdLineArgs the command-line arguments to be processed
 * \param settings the program settings to be modified based upon the arguments received
 * \exception MissingArgument will be emitted if a required argument is not given
 * \exception UnknownArgument will be emitted if an argument is not known
 */
void processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        ProgramSettings& settings);


/**
 * \class MissingArgument
 * \brief Custom exception class for a missing command-line argument
 *
 * Custom exception class for when a known option/flag is not followed by an argument value
 */
class MissingArgument : public std::invalid_argument {
  public:
    /** 
     * \brief Construct a MissingArgument exception
     * \param msg the output diagnostic text
     */
    MissingArgument(const std::string& msg) : std::invalid_argument(msg) {}
};

/**
 * \class UnknownArgument
 * \brief Custom exception class for an unknown command-line argument
 *
 * Custom exception class for when an unknown arguemt is supplied
 */
class UnknownArgument : public std::invalid_argument {
  public:
    /** 
     * \brief Construct an UnknownArgument exception
     * \param msg the output diagnostic text
     */
    UnknownArgument(const std::string& msg) : std::invalid_argument(msg) {}
};

#endif    // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP