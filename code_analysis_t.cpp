/*
  @file code_analysis_t.cpp

  Test program for analysis requests
*/

#include "code_analysis.hpp"

#include <string>
#include <cassert>

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
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
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
        assert(code_analysis(request) == false);
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
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
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
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }

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
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }
    return 0;
}


