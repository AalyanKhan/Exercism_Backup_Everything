#include <array>
#include <string>
#include <vector>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores) {
    // TODO: Implement round_down_scores
    std::vector<int> rounded_scores{};
    for (double score : student_scores){
        rounded_scores.emplace_back(static_cast<int>(score));
    }
    return rounded_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores) {
    // TODO: Implement count_failed_students
    int count_failed_student{};
    for (int score : student_scores){
        if (score <= 40){
            count_failed_student++;
        }
    }
    return count_failed_student;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score) {
    // TODO: Implement letter_grades
    std::array<int, 4> grades{};
    int failing_score{40};
    int passing_score{41};
    highest_score -= failing_score;
    int reminder{highest_score / 4};

    for (int i{0}; i < 4; ++i){ 
        grades[i] = passing_score + (reminder * i);
    }
    
    return grades;
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(
    std::vector<int> student_scores, std::vector<std::string> student_names) {
    // TODO: Implement student_ranking
    std::vector<std::string> rankings{};
    for (size_t i{0}; i < student_scores.size(); ++i){
        std::string rank_line = std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]);
        rankings.push_back(rank_line);
            }
    return rankings;
}

// Create a string that contains the name of the first student to make a perfect
// score on the exam.
std::string perfect_score(std::vector<int> student_scores,
                          std::vector<std::string> student_names) {
    // TODO: Implement perfect_score
    
        for (size_t i{0}; i < student_scores.size(); ++i){
            if (student_scores[i] == 100){
                return student_names[i];
            }
        }
    
    return "";
}
