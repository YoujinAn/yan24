// Name: Youjin An
// Seneca Student ID:140413188
// Seneca email:yan24@myseneca.ca
// Date of completion:13 Feb, 2020

// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"
#include "Book.h"
#include "Book.h"
#include "Movie.h"
#include "Movie.h"
#include "SpellChecker.h"
#include "SpellChecker.h"

using namespace sdds;

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const Collection<Book>& theCollection,
	const Book& theBook)
{
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const Collection<Movie>& theCollection,
	const Movie& theMovie)
{
	std::cout << "Movie \"" << theMovie.title()
		<< "\" added to collection \"" << theCollection.name()
		<< "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the book
	sdds::Collection<sdds::Book> library("Bestsellers");
	{
		// TODO: load the first 4 books from the file "argv[1]".
		//       - read one line at a time, and pass it to the Book constructor
		//       - store each book read into the collection "library" (use the += operator)
		//       - lines that start with "#" are considered comments and should be ignored

		// get the book
		sdds::Collection<sdds::Book> library("Bestsellers");
		{

			std::ifstream file(argv[1]); // call the book file
			size_t count = 0; // count how many times is called
			if (!file) {
				std::cerr << "ERROR: Cannot open file [" << argv[1] << "].\n";
				return 1;
			}
			std::string temBook;
			do
			{
				std::getline(file, temBook);
				if (file) {
					if (temBook[0] != '#') {
						library += sdds::Book(temBook);
						count++;
					}
				}
			} while (count < 4); //save the 4 line
			library.setObserver(bookAddedObserver);

			for (size_t i = 0; i < 3; i++) {
				std::getline(file, temBook);
				if (file) {
					library += sdds::Book(temBook); // add 3 file more after set observer
				}
			}
		}

		double usdToCadRate = 1.3;
		double gbpToCadRate = 1.5;

		// TODO: (from in-lab) create a lambda expression that fixes the price of a book accoding to the rules
		//       - the expression should receive a single parameter of type "Book&"
		//       - if the book was published in US, multiply the price with "usdToCadRate"
		//            and save the new price in the book object
		//       - if the book was published in UK between 1990 and 1999 (inclussive),
		//            multiply the price with "gbpToCadRate" and save the new price in the book object
		auto fixedBookPrice = [=](Book& obj)-> double { // lambda function for adding cadRate
			if (obj.country() == "US") {
				return obj.price() *= usdToCadRate;
			}
			else if (obj.country() == "UK" && obj.year() >= 1990 && obj.year() <= 1999) {
				return obj.price() *= gbpToCadRate;
			}
			else {
				return obj.price();
			}
		};

		std::cout << "-----------------------------------------\n";
		std::cout << "The library content\n";
		std::cout << "-----------------------------------------\n";
		std::cout << library;
		std::cout << "-----------------------------------------\n\n";

		// TODO (from in-lab): iterate over the library and update the price of each book
		//         using the lambda defined above.
		for (size_t i = 0; i < library.size(); i++) {
			fixedBookPrice(library[i]); // used lambda function
		}

		std::cout << "-----------------------------------------\n";
		std::cout << "The library content (updated prices)\n";
		std::cout << "-----------------------------------------\n";
		std::cout << library;
		std::cout << "-----------------------------------------\n\n";

		Collection<Movie> theCollection("Action Movies");

		// Process the file
		Movie movies[5];
		{
			// TODO: load 5 movies from the file "argv[2]".
			//       - read one line at a time, and pass it to the Movie constructor
			//       - store each movie read into the array "movies"
			//       - lines that start with "#" are considered comments and should be ignored
			// open the movie file
			std::ifstream m_file(argv[2]);
			size_t count = 0;
			if (!m_file) {
				std::cerr << "ERROR: Cannot open file [" << argv[2] << "].\n";
				return 1;
			}
			std::string m_temp;
			do {
				std::getline(m_file, m_temp);
				if (m_file) {
					if (m_temp[0] != '#') {
						movies[count] = sdds::Movie(m_temp);
						count++;
					}
				}
			} while (m_file); // call the until file is finished
		}

		std::cout << "-----------------------------------------\n";
		std::cout << "Testing addition and callback function\n";
		std::cout << "-----------------------------------------\n";
		// Add a few movies to collection; no observer is set
		((theCollection += movies[0]) += movies[1]) += movies[2];
		theCollection += movies[1];
		// add more movies; now we get a callback from the collection
		theCollection.setObserver(movieAddedObserver);
		theCollection += movies[3];
		theCollection += movies[3];
		theCollection += movies[4];
		std::cout << "-----------------------------------------\n\n";

		std::cout << "-----------------------------------------\n";
		std::cout << "Testing exceptions and operator[]\n";
		std::cout << "-----------------------------------------\n";

		// TODO: The following loop can generate generate an exception
		//         write code to handle the exception
		//       If an exception occurs print a message in the following format
		//EXCEPTION: ERROR_MESSAGE<endl>
		//         where ERROR_MESSAGE is extracted from the exception object.
		try {
			for (auto i = 0u; i < 10; ++i)
				std::cout << theCollection[i];
		}
		catch (std::exception & e) { // catch the error 
			std::cout << "EXCEPTION: " << e.what() << std::endl;
		}

		std::cout << "-----------------------------------------\n\n";


		std::cout << "-----------------------------------------\n";
		std::cout << "Testing the functor\n";
		std::cout << "-----------------------------------------\n";
		for (auto i = 3u; i <= 4u; ++i)
		{
			// TODO: The following statement can generate generate an exception
			//         write code to handle the exception
			//       If an exception occurs print a message in the following format
			//EXCEPTION: ERROR_MESSAGE<endl>
			//         where ERROR_MESSAGE is extracted from the exception object.
			try { //check the error when we check the spelling
				SpellChecker sp(argv[i]);
				for (auto j = 0u; j < theCollection.size(); ++j)
					theCollection[j].fixSpelling(sp);
				for (auto j = 0u; j < library.size(); ++j)
					library[j].fixSpelling(sp);
			}
			catch (const char* msg) {
				std::cout << "EXCEPTION: " << msg << std::endl;
			}
			catch (std::exception & e) {
				std::cout << "EXCEPTION: " << e.what() << std::endl;
			}

		}
		std::cout << "--------------- Movies ------------------\n";
		std::cout << theCollection;
		std::cout << "--------------- Books -------------------\n";
		std::cout << library;
		std::cout << "-----------------------------------------\n\n";


		std::cout << "-----------------------------------------\n";
		std::cout << "Testing operator[] (the other overload)\n";
		std::cout << "-----------------------------------------\n";
		const Movie* aMovie = theCollection["Terminator 2"];
		if (aMovie == nullptr)
			std::cout << "Movie Terminator 2 not in collection.\n";
		aMovie = theCollection["Dark Phoenix"];
		if (aMovie != nullptr)
			std::cout << "In collection:\n" << *aMovie;
		std::cout << "-----------------------------------------\n\n";

		return 0;
	}
}