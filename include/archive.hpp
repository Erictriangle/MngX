#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP


#include "directory.h"
#include <cstdlib>
#include <vector>
#include <string> 
#include <cstdio>
#include <memory> 
#include <stdexcept>
#include <array>
#include <ctime>
#include <chrono>
#include <boost/algorithm/string.hpp>



/*!
*\brief
*
*Archive class is used to creat archive file, using a 
*linux standard tools like 'tar'.
*
*/


class Archive {
private:
	typedef std::vector<std::string> string_vec;

public:
	Archive() = default;
	Archive(const std::string&);
	Archive(const string_vec&);
	Archive(const Archive&);
	~Archive() = default;

	template <class INPUT> Archive& operator=(const INPUT);
	template <class INPUT> Archive& operator+=(const INPUT);

	void push_back(const std::string&);
	void push_back(const string_vec&);
	void push_back(const Archive&);

	bool creat_archive();
	std::string get_error();

	void clear();
	bool empty() const;
	bool status() const;

private:
	string_vec paths;
	std::string error_output;

	void pop_back();
	std::string back() const;
	bool check_output(const std::string&);

	std::string generate_filename();
};


#endif //ARCHIVE_HPP