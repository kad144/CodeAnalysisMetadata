
# kad144

## Files
% ls

    Makefile
    README.md
    analysis_request.hpp
    code_analysis.cpp
    code_analysis.hpp
    code_analysis_t.cpp
    get_language_from_filename.cpp
    get_language_from_filename.hpp
    get_language_from_filename_t.cpp

## Changed files
% git diff baa2b2fa58cb52ada94597a9b2e5d687f6a3261f --name-only

    code_analysis.cpp
    code_analysis_t.cpp

## Build
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

## Test
% make test

    ./code_analysis_t
    Extension not supported
    Extension not supported
    Extension not supported
    Extension not supported
    Using stdin requires a declared language
    Extension not supported
    Using stdin requires a declared language

## Test Oracle: code\_analysis\_t.cpp
% cp ~collard/CodeAnalysisMetadataEvaluation/code_analysis_t.cpp .  
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

% make test

    ./code_analysis_t
    Extension not supported
    Using stdin requires a declared language

## Test Oracle: code\_analysis.cpp
% cp ~collard/CodeAnalysisMetadataEvaluation/code_analysis.cpp  .  
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

% make test

    ./code_analysis_t
    Extension not supported
    Extension not supported
    Extension not supported
    Extension not supported
    Assertion failed: (filename == ""), function main, file code_analysis_t.cpp, line 198.
    make: *** [test] Abort trap: 6

## Code
% srcml code_analysis.cpp code_analysis_t.cpp -o project.xml
% srcml --xpath="//src:function[src:name='code_analysis']" project.xml | srcml | cat -v

    bool code_analysis(const analysis_request& request) {
    
        auto filename = analysis_filename(request);
    
        auto url = analysis_url(request);
    
        auto language = analysis_language(request, filename);
    
        
        std::string errorType1="Extension not supported";
        std::string errorType2="Using stdin requires a declared language";
        try {
        if(request.given_filename == "-" && language=="")
            throw errorType2;
         if (language=="")
            throw errorType1;        
        }
        catch (std::string &errorType ) {
            std::cerr <<errorType<<std::endl;
            return false;
        }
     
     return true;
        
    }

% srcml --xpath="//src:function[src:name='analysis_filename']" project.xml | srcml | cat -v

    std::string analysis_filename(const analysis_request& request) {
        if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename == "")
            return "";
        if(request.option_filename!="")
            return request.option_filename;
        else if(request.entry_filename == "data")
            return request.given_filename;
        else if((request.entry_filename!="")||(request.given_filename  == "-" && request.entry_filename  != "" && request.option_filename == ""))
            return request.entry_filename;
        else if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename != "")
            return request.option_filename;
        else
    return "";
    }

% srcml --xpath="//src:function[src:name='analysis_url']" project.xml | srcml | cat -v

    std::string analysis_url(const analysis_request& request) {
        if(request.option_url!="")
            return request.option_url;
        if(request.option_url=="")
            return request.given_url;
    return "";
    }

% srcml --xpath="//src:function[src:name='analysis_language']" project.xml | srcml | cat -v

    std::string analysis_language(const analysis_request& request, const std::string& filename) {
        if(request.option_language!="")
            return request.option_language;
       if(request.option_language=="")
            return get_language_from_filename(filename);
    
       return "";
    }

## Test Cases 
% srcml code_analysis_t.cpp --xpath="//src:function[src:name='main']/src:block" | srcml | cat -v

sed: RE error: illegal byte sequence
    {
    
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
    	//test if The filename can be given explicitly as the option_filename
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
            assert(analysis_language(request, filename) == "C++");
            assert(code_analysis(request) == true);
            
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

## Literal Values used in Testing
% srcml code\_analysis_t.cpp --xpath="//src:literal" | srcml | tr '\0' '\n' |grep '"' | sort -u | tr '\n' ','

    "-" "C++" "c++" "data" "main.cpp" "project.tar.gz" "www.FB.com" 
    "www.uakron.edu" 

## Error Messages
% srcml code_analysis.cpp --xpath="//src:function[src:name='code_analysis']//src:expr[contains(., 'cerr')]//src:literal" | srcml | tr '\0'  '\n'


## Commits

### Commit 4f5fc7
% git checkout -q 4f5fc7  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 4f5fc7c468656029cbe3c9466f2938325db808d7
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Sun Apr 1 16:31:12 2018 -0400
    
        added name to test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index b874829..9cbb9c8 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -1,4 +1,5 @@
     /*
    + kenean dukamo
       @file code_analysis.cpp
     
       Implementation of analysis requests

### Commit a6e148
% git checkout -q a6e148  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit a6e1488bafb0d7604dc7c06fc82642725f8a7ff3
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Tue Apr 3 15:50:36 2018 -0400
    
        test if the analysis_filename is retruning the option_filename
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 9cbb9c8..e73dfcc 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -10,7 +10,7 @@
     
     #include <string>
     
    -/** Generate source analysis based on the request
    +/** puGenerate source analysis based on the request
      * @param request Data that forms the request
      * @retval true   Valid request
      * @retval false  Invalid filename or unable to deduce language
    @@ -33,8 +33,10 @@ bool code_analysis(const analysis_request& request) {
      * @retval filename
      */
     std::string analysis_filename(const analysis_request& request) {
    -
    -    return "";
    +    if(request.option_filename!="")
    +    return request.option_filename;
    +    else
    +        return "";
     }
     
     /** URL extracted from the request
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 820446d..1fd665f 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -27,6 +27,23 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +	//The filename can be given explicitly as the option_filename
    + 	{
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "main.cpp";
    +        request.option_url      = "";
    +        request.option_language = "";
     
    +        auto filename = analysis_filename(request);
    +        assert(filename == request.option_filename);
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
         return 0;
     }
    +
    +

### Commit 3aed6a
% git checkout -q 3aed6a  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 3aed6a3678224b003d686325b3baa59daa1d9c0c
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Tue Apr 3 16:27:24 2018 -0400
    
        test if it use the entry_filename for source code archive
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index e73dfcc..6fe8890 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -35,6 +35,8 @@ bool code_analysis(const analysis_request& request) {
     std::string analysis_filename(const analysis_request& request) {
         if(request.option_filename!="")
         return request.option_filename;
    +if(request.entry_filename!="")
    +    return request.entry_filename;
         else
             return "";
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 1fd665f..44782ff 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -43,6 +43,22 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "project.tar.gz";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == request.entry_filename);
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
         return 0;
     }
     

### Commit f69bfa
% git checkout -q f69bfa  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit f69bfa3ef681a7684130137740aafc2eb13bae5a
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Tue Apr 3 17:01:33 2018 -0400
    
        test if a regular file the entry_filename is “data” if it use the given_filename
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 6fe8890..0087996 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -33,8 +33,10 @@ bool code_analysis(const analysis_request& request) {
      * @retval filename
      */
     std::string analysis_filename(const analysis_request& request) {
    -    if(request.option_filename!="")
    +if(request.option_filename!="")
         return request.option_filename;
    +if(request.entry_filename == "data")
    +    return request.given_filename;
     if(request.entry_filename!="")
         return request.entry_filename;
         else
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 44782ff..11c59be 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -59,6 +59,22 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +
    +     {
    +        analysis_request request;
    +        request.given_filename  = "main.cpp";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == request.given_filename);
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
         return 0;
     }
     

### Commit 6bc7a6
% git checkout -q 6bc7a6  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 6bc7a6618cc3e35dd6be85a668ee580aac5ab026
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Tue Apr 3 17:13:40 2018 -0400
    
        test if option_url takes precedence
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 0087996..f0ee7ca 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -48,7 +48,8 @@ if(request.entry_filename!="")
      * @retval URL
      */
     std::string analysis_url(const analysis_request& request) {
    -
    +if(request.option_url!="")
    +    return request.option_url;
         return "";
     }
     
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 11c59be..56dde7b 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -27,7 +27,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -	//The filename can be given explicitly as the option_filename
    +	//tset if The filename can be given explicitly as the option_filename
      	{
             analysis_request request;
             request.given_filename  = "";
    @@ -43,7 +43,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -
    +    //test if it use the entry_filename for source code archive
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -59,7 +59,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -
    +    //test if a regular file the entry_filename is “data” if it use the given_filename
          {
             analysis_request request;
             request.given_filename  = "main.cpp";
    @@ -75,6 +75,22 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "www.FB.com";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == request.option_url);
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
         return 0;
     }
     

### Commit 38c938
% git checkout -q 38c938  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 38c938640769399b107c8a39559fa212e122e364
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Tue Apr 3 17:22:43 2018 -0400
    
        test if option_url is not given to use given_url
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index f0ee7ca..bcb8cea 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -50,6 +50,8 @@ if(request.entry_filename!="")
     std::string analysis_url(const analysis_request& request) {
     if(request.option_url!="")
         return request.option_url;
    +if(request.option_url=="")
    +    return request.given_url;
         return "";
     }
     
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 56dde7b..3e892c7 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -75,7 +75,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -
    +    // test if option_url takes precedence
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -91,6 +91,22 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "www.uakron.edu";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == request.given_url);
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
         return 0;
     }
     

### Commit 881ba1
% git checkout -q 881ba1  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 881ba18ea14812de19498d39529336752551434e
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Tue Apr 3 18:19:49 2018 -0400
    
        //test if the language can be explicitly given as option_language
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index bcb8cea..e92c8ab 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -61,6 +61,8 @@ if(request.option_url=="")
      * @retval language
      */
     std::string analysis_language(const analysis_request& request, const std::string& filename) {
    +    if(request.option_language!="")
    +        return request.option_language;
     
         return "";
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 3e892c7..f1a6842 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -91,7 +91,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -
    +//test if option_url is not given to use given_url
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -107,6 +107,22 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "main.cpp";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == request.option_language);
    +        assert(code_analysis(request) == false);
    +    }
         return 0;
     }
     

### Commit 024bd4
% git checkout -q 024bd4  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 024bd44e586abdbd03661bb8b6f2c66d42d1205a
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Tue Apr 3 18:28:48 2018 -0400
    
        test if the language can be explicitly given as option_language
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index f1a6842..365a117 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -107,7 +107,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -
    +    //test if the language can be explicitly given as option_language
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -115,7 +115,7 @@ int main() {
             request.given_url       = "";
             request.option_filename = "";
             request.option_url      = "";
    -        request.option_language = "main.cpp";
    +        request.option_language = "c++";
     
             auto filename = analysis_filename(request);
             assert(filename == "");

### Commit ab4811
% git checkout -q ab4811  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit ab48112317e0e29e33b6943ffb8618cf1ca8fd05
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Wed Apr 4 13:23:45 2018 -0400
    
        test if when the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index e92c8ab..cb16caf 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -63,6 +63,8 @@ if(request.option_url=="")
     std::string analysis_language(const analysis_request& request, const std::string& filename) {
         if(request.option_language!="")
             return request.option_language;
    +    else
    +        return get_language_from_filename(filename);
     
    -    return "";
    +   return "";
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 365a117..c7372a4 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -5,9 +5,11 @@
     */
     
     #include "code_analysis.hpp"
    +#include "get_language_from_filename.hpp"
     
     #include <string>
     #include <cassert>
    +#include <iostream>
     
     int main() {
     
    @@ -40,7 +42,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == request.option_filename);
             assert(analysis_url(request) == "");
    -        assert(analysis_language(request, filename) == "");
    +        //assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
         //test if it use the entry_filename for source code archive
    @@ -72,7 +74,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == request.given_filename);
             assert(analysis_url(request) == "");
    -        assert(analysis_language(request, filename) == "");
    +        //assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
         // test if option_url takes precedence
    @@ -88,7 +90,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.option_url);
    -        assert(analysis_language(request, filename) == "");
    +        //assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
     //test if option_url is not given to use given_url
    @@ -104,7 +106,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.given_url);
    -        assert(analysis_language(request, filename) == "");
    +        //assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
         //test if the language can be explicitly given as option_language
    @@ -123,6 +125,40 @@ int main() {
             assert(analysis_language(request, filename) == request.option_language);
             assert(code_analysis(request) == false);
         }
    +    //test if the langeuage is not given if it uses get_language_from_filename() function to get the language
    +   {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "main.cpp";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == request.option_filename);
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == get_language_from_filename(filename));
    +        assert(code_analysis(request) == false);
    +    }
    +
    +//test if when the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename 
    +
    +    {
    +        analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "main.cpp";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == request.option_filename);
    +        assert(code_analysis(request) == false);
    +
    +    } 
    +
         return 0;
     }
     

### Commit 8f2982
% git checkout -q 8f2982  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 8f2982bca584c0f0db8cfdca118dca924db2d37a
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Wed Apr 4 20:16:00 2018 -0400
    
        test if the given_filename is from standard input and entry_filename is given if return  entry_filename
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index cb16caf..b14d5b7 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -10,6 +10,8 @@
     
     #include <string>
     
    +#include <iostream>
    +
     /** puGenerate source analysis based on the request
      * @param request Data that forms the request
      * @retval true   Valid request
    @@ -23,9 +25,9 @@ bool code_analysis(const analysis_request& request) {
     
         auto language = analysis_language(request, filename);
     
    -    // code analysis processing that is not yet implemented
    -
    +    
         return false;
    +    
     }
     
     /** Filename extracted from the request
    @@ -39,6 +41,12 @@ if(request.entry_filename == "data")
         return request.given_filename;
     if(request.entry_filename!="")
         return request.entry_filename;
    +if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename != "")
    +    return request.option_filename;
    +if(request.given_filename  == "-" && request.entry_filename  != "" && request.option_filename == "")
    +    return request.entry_filename;
    +if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename == "")
    +    return request.entry_filename;
         else
             return "";
     }
    @@ -63,7 +71,7 @@ if(request.option_url=="")
     std::string analysis_language(const analysis_request& request, const std::string& filename) {
         if(request.option_language!="")
             return request.option_language;
    -    else
    +   if(request.option_language=="")
             return get_language_from_filename(filename);
     
        return "";
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index c7372a4..27790e7 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -42,8 +42,8 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == request.option_filename);
             assert(analysis_url(request) == "");
    -        //assert(analysis_language(request, filename) == "");
    -        assert(code_analysis(request) == false);
    +        
    +        //assert(code_analysis(request) == false);
         }
         //test if it use the entry_filename for source code archive
         {
    @@ -74,7 +74,6 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == request.given_filename);
             assert(analysis_url(request) == "");
    -        //assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
         // test if option_url takes precedence
    @@ -90,7 +89,6 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.option_url);
    -        //assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
     //test if option_url is not given to use given_url
    @@ -106,7 +104,6 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.given_url);
    -        //assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
         //test if the language can be explicitly given as option_language
    @@ -159,6 +156,26 @@ int main() {
     
         } 
     
    +//test if the given_filename is from standard input and entry_filename is given if return  entry_filename 
    +    {
    +        analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "main.cpp";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == request.entry_filename);
    +        assert(code_analysis(request) == false);
    +
    +    }
    +
    +    
    +
    +    
    +    //*/
         return 0;
     }
     

### Commit 77768b
% git checkout -q 77768b  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 77768b97dc2d7f908a51e2f78cea30f481573124
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Wed Apr 4 20:27:39 2018 -0400
    
        test if the given_filename is from standard input, entry_filename is data and option_filename is blank then retruns black.
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index b14d5b7..496c79b 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -35,6 +35,8 @@ bool code_analysis(const analysis_request& request) {
      * @retval filename
      */
     std::string analysis_filename(const analysis_request& request) {
    +if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename == "")
    +    return "";
     if(request.option_filename!="")
         return request.option_filename;
     if(request.entry_filename == "data")
    @@ -45,8 +47,6 @@ if(request.given_filename  == "-" && request.entry_filename  == "data" && reques
         return request.option_filename;
     if(request.given_filename  == "-" && request.entry_filename  != "" && request.option_filename == "")
         return request.entry_filename;
    -if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename == "")
    -    return request.entry_filename;
         else
             return "";
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 27790e7..df7e20f 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -139,7 +139,7 @@ int main() {
             assert(code_analysis(request) == false);
         }
     
    -//test if when the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename 
    +//test if the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename 
     
         {
             analysis_request request;
    @@ -171,11 +171,25 @@ int main() {
             assert(code_analysis(request) == false);
     
         }
    +//test if the given_filename is from standard input, entry_filename is "data" and option_filename is blank then retruns black.
    +{
    +        analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
     
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == request.option_language);
    +        assert(code_analysis(request) == false);
    +    }
         
     
         
    -    //*/
         return 0;
     }
     

### Commit 7878a4
% git checkout -q 7878a4  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 7878a457b696396176a5fb3af1a218d77cf49b4a
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Thu Apr 5 01:03:46 2018 -0400
    
        test If the file extension is used to determine the language, and there is no mapping for that language, output the error message
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 496c79b..bf0339b 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -26,7 +26,27 @@ bool code_analysis(const analysis_request& request) {
         auto language = analysis_language(request, filename);
     
         
    +    std::string errorType1="Extension not supported";
    +std::string errorType2="Using stdin requires a declared language";
    +    try {
    +    
    +    if (language=="")
    +    {
    +        throw errorType1;
    +          
    +    }
    +    if(request.given_filename == "-" && language=="")
    +    {
    +        throw errorType2;
    +    }
    +    
    +}
    +catch (std::string &errorType ) {
    +    std::cerr <<errorType<<std::endl;
         return false;
    +}
    + 
    + return true;
         
     }
     
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index df7e20f..617056f 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -43,7 +43,7 @@ int main() {
             assert(filename == request.option_filename);
             assert(analysis_url(request) == "");
             
    -        //assert(code_analysis(request) == false);
    +        
         }
         //test if it use the entry_filename for source code archive
         {
    @@ -59,7 +59,7 @@ int main() {
             assert(filename == request.entry_filename);
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == "");
    -        assert(code_analysis(request) == false);
    +        
         }
         //test if a regular file the entry_filename is “data” if it use the given_filename
          {
    @@ -74,7 +74,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == request.given_filename);
             assert(analysis_url(request) == "");
    -        assert(code_analysis(request) == false);
    +        
         }
         // test if option_url takes precedence
         {
    @@ -89,7 +89,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.option_url);
    -        assert(code_analysis(request) == false);
    +        
         }
     //test if option_url is not given to use given_url
         {
    @@ -104,7 +104,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.given_url);
    -        assert(code_analysis(request) == false);
    +        
         }
         //test if the language can be explicitly given as option_language
         {
    @@ -120,7 +120,7 @@ int main() {
             assert(filename == "");
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == request.option_language);
    -        assert(code_analysis(request) == false);
    +        
         }
         //test if the langeuage is not given if it uses get_language_from_filename() function to get the language
        {
    @@ -136,7 +136,7 @@ int main() {
             assert(filename == request.option_filename);
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == get_language_from_filename(filename));
    -        assert(code_analysis(request) == false);
    +        
         }
     
     //test if the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename 
    @@ -152,7 +152,7 @@ int main() {
     
             auto filename = analysis_filename(request);
             assert(filename == request.option_filename);
    -        assert(code_analysis(request) == false);
    +        
     
         } 
     
    @@ -168,7 +168,7 @@ int main() {
     
             auto filename = analysis_filename(request);
             assert(filename == request.entry_filename);
    -        assert(code_analysis(request) == false);
    +        
     
         }
     //test if the given_filename is from standard input, entry_filename is "data" and option_filename is blank then retruns black.
    @@ -185,9 +185,18 @@ int main() {
             assert(filename == "");
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == request.option_language);
    -        assert(code_analysis(request) == false);
    +       
         }
    -    
    +
    +
    + //test If the file extension is used to determine the language, and there is no mapping for that language, output the error message 
    +{
    +	analysis_request request;
    +	request.option_language = "";
    +	assert(code_analysis(request) == false);
    +}
    +
    +
     
         
         return 0;

### Commit 87690e
% git checkout -q 87690e  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 87690e44046f023f9259390e551b12713dea9edd
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Thu Apr 5 01:11:04 2018 -0400
    
        test When the input is from standard input and a language cannot be determined, output the error message
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index bf0339b..4f969d5 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -29,16 +29,18 @@ bool code_analysis(const analysis_request& request) {
         std::string errorType1="Extension not supported";
     std::string errorType2="Using stdin requires a declared language";
         try {
    +
    +    if(request.given_filename == "-" && language=="")
    +    {
    +        throw errorType2;
    +    }
         
         if (language=="")
         {
             throw errorType1;
               
         }
    -    if(request.given_filename == "-" && language=="")
    -    {
    -        throw errorType2;
    -    }
    +    
         
     }
     catch (std::string &errorType ) {
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 617056f..ced73af 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -193,11 +193,17 @@ int main() {
     {
     	analysis_request request;
     	request.option_language = "";
    +	request.given_filename  = "";
     	assert(code_analysis(request) == false);
     }
     
    -
    -
    +//test When the input is from standard input and a language cannot be determined, output the error message
    +{
    +	analysis_request request;
    +	request.given_filename = "-";
    +	request.option_language = "";
    +	assert(code_analysis(request) == false);
    +}
         
         return 0;
     }

### Commit 77c812
% git checkout -q 77c812  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 77c812d2658b788bd2a9378329881d7c01045950
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Thu Apr 5 12:52:41 2018 -0400
    
        test if valid filename to return true
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 4f969d5..20163c4 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -26,21 +26,19 @@ bool code_analysis(const analysis_request& request) {
         auto language = analysis_language(request, filename);
     
         
    -    std::string errorType1="Extension not supported";
    +std::string errorType1="Extension not supported";
     std::string errorType2="Using stdin requires a declared language";
         try {
    -
    -    if(request.given_filename == "-" && language=="")
    -    {
    -        throw errorType2;
    -    }
         
         if (language=="")
         {
             throw errorType1;
               
         }
    -    
    +    if(request.given_filename == "-" && language=="")
    +    {
    +        throw errorType2;
    +    }
         
     }
     catch (std::string &errorType ) {
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index ced73af..1512164 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -204,6 +204,14 @@ int main() {
     	request.option_language = "";
     	assert(code_analysis(request) == false);
     }
    +
    +//test valid filename retrun true
    +{
    +	analysis_request request;
    +	request.given_filename = "";
    +	request.option_language = "main.cpp";
    +	assert(code_analysis(request) == true);
    +}
         
         return 0;
     }

### Commit 5dd2df
% git checkout -q 5dd2df  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 5dd2df8d094eaaa98b665b1ffe06fd1365a78e13
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Fri Apr 6 14:26:06 2018 -0400
    
        update test case:test if The filename can be given explicitly as the option_filename
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 20163c4..db229ed 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -29,16 +29,16 @@ bool code_analysis(const analysis_request& request) {
     std::string errorType1="Extension not supported";
     std::string errorType2="Using stdin requires a declared language";
         try {
    -    
    +    if(request.given_filename == "-" && language=="")
    +    {
    +        throw errorType2;
    +    }   
         if (language=="")
         {
             throw errorType1;
               
         }
    -    if(request.given_filename == "-" && language=="")
    -    {
    -        throw errorType2;
    -    }
    +    
         
     }
     catch (std::string &errorType ) {
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 1512164..0a4b91c 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -42,7 +42,8 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == request.option_filename);
             assert(analysis_url(request) == "");
    -        
    +        assert(analysis_language(request, filename) == "C++");
    +        assert(code_analysis(request) == true);
             
         }
         //test if it use the entry_filename for source code archive
    @@ -205,7 +206,7 @@ int main() {
     	assert(code_analysis(request) == false);
     }
     
    -//test valid filename retrun true
    +//test if valid filename to return true
     {
     	analysis_request request;
     	request.given_filename = "";

### Commit e73710
% git checkout -q e73710  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit e7371071cc344ea6a8d08ae6e99e60f769417853
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Fri Apr 6 16:45:17 2018 -0400
    
        updated analysis_filename() if statemnt is more simple
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index db229ed..87328e4 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -26,25 +26,18 @@ bool code_analysis(const analysis_request& request) {
         auto language = analysis_language(request, filename);
     
         
    -std::string errorType1="Extension not supported";
    -std::string errorType2="Using stdin requires a declared language";
    +    std::string errorType1="Extension not supported";
    +    std::string errorType2="Using stdin requires a declared language";
         try {
         if(request.given_filename == "-" && language=="")
    -    {
             throw errorType2;
    -    }   
    -    if (language=="")
    -    {
    -        throw errorType1;
    -          
    +     if (language=="")
    +        throw errorType1;        
    +    }
    +    catch (std::string &errorType ) {
    +        std::cerr <<errorType<<std::endl;
    +        return false;
         }
    -    
    -    
    -}
    -catch (std::string &errorType ) {
    -    std::cerr <<errorType<<std::endl;
    -    return false;
    -}
      
      return true;
         
    @@ -55,18 +48,18 @@ catch (std::string &errorType ) {
      * @retval filename
      */
     std::string analysis_filename(const analysis_request& request) {
    -if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename == "")
    -    return "";
    -if(request.option_filename!="")
    -    return request.option_filename;
    -if(request.entry_filename == "data")
    -    return request.given_filename;
    -if(request.entry_filename!="")
    -    return request.entry_filename;
    -if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename != "")
    -    return request.option_filename;
    -if(request.given_filename  == "-" && request.entry_filename  != "" && request.option_filename == "")
    -    return request.entry_filename;
    +    if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename == "")
    +        return "";
    +    if(request.option_filename!="")
    +        return request.option_filename;
    +    else if(request.entry_filename == "data")
    +        return request.given_filename;
    +//else if(request.entry_filename!="")
    +    //return request.entry_filename;
    +    else if((request.entry_filename!="")||(request.given_filename  == "-" && request.entry_filename  != "" && request.option_filename == ""))
    +        return request.entry_filename;
    +    else if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename != "")
    +        return request.option_filename;
         else
             return "";
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 0a4b91c..9ff91cc 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -29,7 +29,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -	//tset if The filename can be given explicitly as the option_filename
    +	//test if The filename can be given explicitly as the option_filename
      	{
             analysis_request request;
             request.given_filename  = "";
    @@ -46,7 +46,7 @@ int main() {
             assert(code_analysis(request) == true);
             
         }
    -    //test if it use the entry_filename for source code archive
    +	//test if it use the entry_filename for source code archive
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -60,9 +60,10 @@ int main() {
             assert(filename == request.entry_filename);
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
             
         }
    -    //test if a regular file the entry_filename is “data” if it use the given_filename
    +	//test if a regular file the entry_filename is “data” if it use the given_filename
          {
             analysis_request request;
             request.given_filename  = "main.cpp";
    @@ -75,9 +76,10 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == request.given_filename);
             assert(analysis_url(request) == "");
    -        
    +        assert(analysis_language(request, filename) == "C++");
    +        assert(code_analysis(request) == true);
         }
    -    // test if option_url takes precedence
    +	// test if option_url takes precedence
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -90,9 +92,11 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.option_url);
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
             
         }
    -//test if option_url is not given to use given_url
    +	//test if option_url is not given to use given_url
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -105,7 +109,8 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == request.given_url);
    -        
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
         }
         //test if the language can be explicitly given as option_language
         {
    @@ -121,6 +126,7 @@ int main() {
             assert(filename == "");
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == request.option_language);
    +        assert(code_analysis(request) == true);
             
         }
         //test if the langeuage is not given if it uses get_language_from_filename() function to get the language
    @@ -137,10 +143,11 @@ int main() {
             assert(filename == request.option_filename);
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == get_language_from_filename(filename));
    +        assert(code_analysis(request) == true);
             
         }
     
    -//test if the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename 
    +	//test if the given_filename is from standard input and entry_filename is a non source code archive if it uses the option_filename 
     
         {
             analysis_request request;
    @@ -153,11 +160,13 @@ int main() {
     
             auto filename = analysis_filename(request);
             assert(filename == request.option_filename);
    -        
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == get_language_from_filename(filename));
    +        assert(code_analysis(request) == true);
     
         } 
     
    -//test if the given_filename is from standard input and entry_filename is given if return  entry_filename 
    +	//test if the given_filename is from standard input and entry_filename is given if return  entry_filename 
         {
             analysis_request request;
             request.given_filename  = "-";
    @@ -169,11 +178,14 @@ int main() {
     
             auto filename = analysis_filename(request);
             assert(filename == request.entry_filename);
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == get_language_from_filename(filename));
    +        assert(code_analysis(request) == true);
             
     
         }
    -//test if the given_filename is from standard input, entry_filename is "data" and option_filename is blank then retruns black.
    -{
    +	//test if the given_filename is from standard input, entry_filename is "data" and option_filename is blank then retruns black.
    +	{
             analysis_request request;
             request.given_filename  = "-";
             request.entry_filename  = "data";
    @@ -185,34 +197,64 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == "");
    -        assert(analysis_language(request, filename) == request.option_language);
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
            
         }
     
     
    - //test If the file extension is used to determine the language, and there is no mapping for that language, output the error message 
    -{
    -	analysis_request request;
    -	request.option_language = "";
    -	request.given_filename  = "";
    -	assert(code_analysis(request) == false);
    -}
    + 	//test If the file extension is used to determine the language, and there is no mapping for that language, output the error message 
    +	{
     
    -//test When the input is from standard input and a language cannot be determined, output the error message
    -{
    -	analysis_request request;
    -	request.given_filename = "-";
    -	request.option_language = "";
    -	assert(code_analysis(request) == false);
    -}
    +		analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
     
    -//test if valid filename to return true
    -{
    -	analysis_request request;
    -	request.given_filename = "";
    -	request.option_language = "main.cpp";
    -	assert(code_analysis(request) == true);
    -}
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +	}
    +
    +	//test When the input is from standard input and a language cannot be determined, output the error message
    +	{
    +
    +		analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +	}	
    +
    +	//test if valid filename to return true
    +	{
    +		analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "main.cpp";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == request.entry_filename);
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "C++");
    +        assert(code_analysis(request) == true);
    +	}
         
         return 0;
     }

### Commit 759472
% git checkout -q 759472  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 759472a5259fde271dcb2ebb583b8879c505f073
    Author: kenean dukamo <kad144@zips.uakorn.edu>
    Date:   Fri Apr 6 16:56:14 2018 -0400
    
        code indentation and last commit
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 87328e4..2308121 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -1,5 +1,4 @@
     /*
    - kenean dukamo
       @file code_analysis.cpp
     
       Implementation of analysis requests
    @@ -54,14 +53,12 @@ std::string analysis_filename(const analysis_request& request) {
             return request.option_filename;
         else if(request.entry_filename == "data")
             return request.given_filename;
    -//else if(request.entry_filename!="")
    -    //return request.entry_filename;
         else if((request.entry_filename!="")||(request.given_filename  == "-" && request.entry_filename  != "" && request.option_filename == ""))
             return request.entry_filename;
         else if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename != "")
             return request.option_filename;
         else
    -        return "";
    +return "";
     }
     
     /** URL extracted from the request
    @@ -69,11 +66,11 @@ std::string analysis_filename(const analysis_request& request) {
      * @retval URL
      */
     std::string analysis_url(const analysis_request& request) {
    -if(request.option_url!="")
    -    return request.option_url;
    -if(request.option_url=="")
    -    return request.given_url;
    -    return "";
    +    if(request.option_url!="")
    +        return request.option_url;
    +    if(request.option_url=="")
    +        return request.given_url;
    +return "";
     }
     
     /** Language extracted from the request and the filename

