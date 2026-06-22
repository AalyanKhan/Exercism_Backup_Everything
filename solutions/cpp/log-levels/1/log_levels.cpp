#include <string>

namespace log_line {

std::string message(std::string line) {
    // Find the end of the log level prefix ": "
    size_t delimiter_pos = line.find(": ");
    
    // Extract everything starting right after the space
    return line.substr(delimiter_pos + 2);
}

std::string log_level(std::string line) {
    // Find the positions of the enclosing brackets
    size_t start = line.find('[') + 1;
    size_t end = line.find(']');
    
    // Extract the substring between the brackets
    return line.substr(start, end - start);
}

std::string reformat(std::string line) {
    // Reuse our two functions to extract the necessary parts
    std::string msg = message(line);
    std::string level = log_level(line);
    
    // Combine them into the target format
    return msg + " (" + level + ")";
}

}  // namespace log_line
