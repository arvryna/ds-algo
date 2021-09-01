// Tokenize article into strings and load it to vector
void TokenizeStringIntoVector(const std::string &article, std::vector<std::string> &words) {
    std::string word = "";
    for (size_t i = 0; i < article.size(); i++) {
        if (article[i] != ' ') {
            word.push_back(article[i]);
        } else {
            words.push_back(word);
            word = "";
        }
    }
    words.push_back(word);
}

std::string IsProgressingSequence(const std::vector<int> &list) {
    int diff = std::abs(list[0] - list[1]);
    for (size_t i = 0; i < list.size() - 1; i++) {
        if (std::abs(list[i] - list[i + 1]) != diff) {
            return "no";
        }
    }
    return "yes";
}
