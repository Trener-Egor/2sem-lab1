#include <iostream>
#include <string>
#include <vector>
#include<fstream>
class student 
{
public:
	student()
	{
		std::cout << this<<std::endl;
	}
	student(const std::string& f, const std::string& i, const std::string& o)
	{
		this->f_ = f;
		this->i_ = i;
		this->o_ = o;
	}
	std::string get_f() const {
		return f_;
	}
	std::string get_i() const {
		return i_;
	}
	std::string get_o() const {
		return o_;
	}
	std::vector<uint8_t>& get_scores() {
		return scores_;
	}
	void print_fio()
	{
		std::cout << f_ << ' ' << i_  <<  ' ' <<  o_ << "\n";
	}
	void print_scores()
	{
		for (int i = 0; i < scores_.size(); ++i) {
			std::cout << (int)scores_[i] << ' ';
		}
		std::cout << "\n";
	}
	void add_new_score(uint8_t s) 
	{
		scores_.push_back(s);
	}
	bool grants() const
	{
		for (int i = 0; i < scores_.size(); ++i) {
			if (scores_[i] < 4) {
				return false;
			}
		}
		return true;
	}
private:
	std::string f_;
	std::string i_;
	std::string o_;
	std::vector<uint8_t> scores_;
};

std::vector<student> read_from_file(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "file didnt open\n";
		return {};
	}
	std::vector<student> students;

	while (!file.eof()) {
		std::string s1;
		std::string s2;
		std::string s3;
		file >> s1 >> s2 >> s3;
		student st(s1, s2, s3);

		int n;
		file >> n;

		for (int i = 0; i < n; ++i) {
			int b;
			file >> b;
			st.add_new_score(b);
		}
		students.push_back(st);
	}
	return students;
}

void write_to_file(const std::string& filename, const std::vector<student>& students) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cout << "cant create file\n";
		return;
	}
	for (int i = 0; i < students.size(); ++i) {
		if (students[i].grants()) {
			file << students[i].get_f() << ' '
				<< students[i].get_i() << ' '
				<< students[i].get_o() << '\n';
		}
	}
	file.close();
}



int main()
{	
	std::vector<student> students = read_from_file("Students.txt");

	if (students.empty()) {
		std::cout << "file is empty\n";
		return 0;
	}
	for (int i = 0; i < students.size(); ++i) {
		if (students[i].grants()) {
			students[i].print_fio();
			students[i].print_scores();
		}
	}
	write_to_file("out.txt",students);
}
