/*
  @file code_analysis_t.cpp

  Test program for analysis requests
*/

#include "code_analysis.hpp"
#include "get_language_from_filename.hpp"

#include <string>
#include <cassert>
#include <iostream>

int main() {

    // all parts of the request are empty
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }
	//tset if The filename can be given explicitly as the option_filename
 	{
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "main.cpp";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == request.option_filename);
        assert(analysis_url(request) == "");
        
        
    }
    //test if it use the entry_filename for source code archive
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "project.tar.gz";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == request.entry_filename);
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "");
        
    }
    //test if a regular file the entry_filename is “data” if it use the given_filename
     {
        analysis_request request;
        request.given_filename  = "main.cpp";
        request.entry_filename  = "data";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == request.given_filename);
        assert(analysis_url(request) == "");
        
    }
    // test if option_url takes precedence
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "www.FB.com";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == request.option_url);
        
    }
//test if option_url is not given to use given_url
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "www.uakron.edu";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == request.given_url);
        
    }
    //test if the language can be explicitly given as option_language
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "c++";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == request.option_language);
        
    }
    //test if the langeuage is not given if it uses get_language_from_filename() function to get the language
   {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "main.cpp";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == request.option_filename);
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == get_language_from_filename(filename));
        
    }

//test if the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename 

    {
        analysis_request request;
        request.given_filename  = "-";
        request.entry_filename  = "data";
        request.given_url       = "";
        request.option_filename = "main.cpp";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == request.option_filename);
        

    } 

//test if the given_filename is from standard input and entry_filename is given if return  entry_filename 
    {
        analysis_request request;
        request.given_filename  = "-";
        request.entry_filename  = "main.cpp";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == request.entry_filename);
        

    }
//test if the given_filename is from standard input, entry_filename is "data" and option_filename is blank then retruns black.
{
        analysis_request request;
        request.given_filename  = "-";
        request.entry_filename  = "data";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == request.option_language);
       
    }


 //test If the file extension is used to determine the language, and there is no mapping for that language, output the error message 
{
	analysis_request request;
	request.option_language = "";
	request.given_filename  = "";
	assert(code_analysis(request) == false);
}

//test When the input is from standard input and a language cannot be determined, output the error message
{
	analysis_request request;
	request.given_filename = "-";
	request.option_language = "";
	assert(code_analysis(request) == false);
}
    
    return 0;
}


