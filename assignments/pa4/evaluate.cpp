#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string removeSpaces(string submit) {
  while (!submit.empty() && isspace(*submit.begin()))
    submit.erase(submit.begin());

  while (!submit.empty() && isspace(*submit.rbegin()))
    submit.erase(submit.length() - 1);

  while (submit.empty() && isspace(*submit.rbegin()))
    submit.erase(submit.length() - 1);

  return submit;
}
// Code from
// https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
std::istream &safeGetline(std::istream &is, std::string &t) {
  t.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(is, true);
  std::streambuf *sb = is.rdbuf();

  for (;;) {
    int c = sb->sbumpc();
    switch (c) {
    case '\n':
      return is;
    case '\r':
      if (sb->sgetc() == '\n')
        sb->sbumpc();
      return is;
    case std::streambuf::traits_type::eof():
      // Also handle the case when the last line has no line ending
      if (t.empty())
        is.setstate(std::ios::eofbit);
      return is;
    default:
      t += (char)c;
    }
  }
}
void readFile(const string filename, vector<string> &lines) {
  string line;
  int task_num = 0;

  // Open file
  ifstream fin;
  fin.open(filename.c_str());
  if (!fin.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    exit(1);
  }

  // Read & push to string vector
  while (safeGetline(fin, line)) {
    line = removeSpaces(line);
    if (line.substr(0, 6).compare("[Task ") == 0) {
      // The first line of a new task
      task_num++;
      lines.push_back(line);
    } else if (task_num >= 1) {
      // Answer of the task
      lines[task_num - 1] = lines[task_num - 1] + "\n" + line;
    } else {
      cerr << "Unexpected file format: " << filename << endl;
      exit(-1);
    }
  }

  fin.close();
  return;
}

int main(int argc, char **argv) {
  vector<int> scores;
  int total_score = 0;
  vector<string> submit;
  vector<string> answer;

  // Scores
  if (argc == 1) {
    int sample[8] = {2, 1, 2, 2, 2, 2, 2, 2};
    scores.insert(scores.end(), sample, sample + 8);
  } else {
    for (int i = 1; i < argc; i++) {
      int score = atoi(argv[i]);
      scores.push_back(score);
    }
  }

  // Read submit.txt & answer.txt
  readFile("submit.txt", submit);
  readFile("answer.txt", answer);

  // Add score if submit and answer are the same
  for (int i = 0; i < min(submit.size(), answer.size()); i++) {
    submit[i] = removeSpaces(submit[i]);
    answer[i] = removeSpaces(answer[i]);

    if (submit[i].compare(answer[i]) == 0)
      total_score += scores[i];
  }
  cout << "Your score is " << total_score << endl;

  return 0;
}
