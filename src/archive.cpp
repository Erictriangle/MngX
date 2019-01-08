#include "archive.hpp"

//=================
//==CONSTRUCTORS==
//===============


Archive::Archive(const std::string& path_) {
	push_back(path_);
}

Archive::Archive(const string_vec& path_) {
	push_back(path_);
}

Archive::Archive(const Archive& path_) {
	push_back(path_);
}


//=============
//==TEMPLATE==
//===========


template <class INPUT>
Archive& Archive::operator=(const INPUT path_) {
	clear();
	push_back(path_);
	return *this;
}


template <class INPUT>
Archive& Archive::operator+=(const INPUT path_) {
	push_back(path_);
	return *this;
}


//===========
//==PUBLIC==
//=========


void
Archive::push_back(const std::string& path_) {
	paths.push_back(path_);
}


void
Archive::push_back(const string_vec& path_) {
	for (auto i : path_)
		paths.push_back(i);
}


void 
Archive::push_back(const Archive& path_) {
	for (auto p : path_.paths)
		paths.push_back(p);
}


bool 
Archive::creat_archive() {
	std::array<char, 128> buffer;
	std::string output;
	std::string cmd{ "tar cfzv " };
	cmd += generate_filename() + " ";
	for (auto p : paths) {
		cmd += p;
		cmd += " ";
	}
	cmd += "2>&1"; //stderr >> stdout

	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

	if (!pipe)
		throw std::runtime_error("-=[ EXCEPTION ]=-  cannot create 'tar' process");

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		output += buffer.data();

	if (!check_output(output)) {
		error_output = output;
		return 0;
	}

	return 1;
}


std::string
Archive::get_error() {
	return error_output;
}


bool
Archive::empty() const {
	return paths.empty();
}


void
Archive::clear() {
	paths.clear();
}


bool
Archive::status() const{
	return !error_output.empty();
}

//============
//==PRIVATE==
//==========


void
Archive::pop_back() {
	paths.pop_back();
}


std::string
Archive::back() const {
	if (paths.empty())
		return "";
	return paths.back();
}


bool 
Archive::check_output(const std::string& output) {
	string_vec temp;
	boost::split(temp, output, boost::is_any_of(" "));

	if (temp.size() != paths.size())
		return 0;

	for (unsigned int i = 0; i < paths.size(); i++)
		if (paths[i] != temp[i])
			return 0;
	return 1;
}


std::string
Archive::generate_filename() {
	std::time_t time =
		std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::string user = getenv("USER");
	std::string temp = ctime(&time);
	std::string time_str;
	
	//day
	if (temp.substr(8, 1) == " ")
		time_str = "0" + temp.substr(9, 1) + "-";
	else
		time_str = temp.substr(8, 2) + "-";

	time_str += temp.substr(4, 3) + "-"; //month
	time_str += temp.substr(20,4) + "-"; //year
	time_str +=  temp.substr(11, 2) + "-"; //time - hour
	time_str += temp.substr(14, 2) + "-"; //time - minutes
	time_str += temp.substr(17, 2); //time - seconds

	return user + "-" + time_str;
}
