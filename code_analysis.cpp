/*
 kenean dukamo
  @file code_analysis.cpp

  Implementation of analysis requests
*/

#include "code_analysis.hpp"
#include "get_language_from_filename.hpp"

#include <string>

#include <iostream>

/** puGenerate source analysis based on the request
 * @param request Data that forms the request
 * @retval true   Valid request
 * @retval false  Invalid filename or unable to deduce language
 */
bool code_analysis(const analysis_request& request) {

    auto filename = analysis_filename(request);

    auto url = analysis_url(request);

    auto language = analysis_language(request, filename);

    
    std::string errorType1="Extension not supported";
std::string errorType2="Using stdin requires a declared language";
    try {

    if(request.given_filename == "-" && language=="")
    {
        throw errorType2;
    }
    
    if (language=="")
    {
        throw errorType1;
          
    }
    
    
}
catch (std::string &errorType ) {
    std::cerr <<errorType<<std::endl;
    return false;
}
 
 return true;
    
}

/** Filename extracted from the request
 * @param  request Data that forms the request
 * @retval filename
 */
std::string analysis_filename(const analysis_request& request) {
if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename == "")
    return "";
if(request.option_filename!="")
    return request.option_filename;
if(request.entry_filename == "data")
    return request.given_filename;
if(request.entry_filename!="")
    return request.entry_filename;
if(request.given_filename  == "-" && request.entry_filename  == "data" && request.option_filename != "")
    return request.option_filename;
if(request.given_filename  == "-" && request.entry_filename  != "" && request.option_filename == "")
    return request.entry_filename;
    else
        return "";
}

/** URL extracted from the request
 * @param  request Data that forms the request
 * @retval URL
 */
std::string analysis_url(const analysis_request& request) {
if(request.option_url!="")
    return request.option_url;
if(request.option_url=="")
    return request.given_url;
    return "";
}

/** Language extracted from the request and the filename
 * @param  request Data that forms the request
 * @param  filename Filename extracted from the request
 * @retval language
 */
std::string analysis_language(const analysis_request& request, const std::string& filename) {
    if(request.option_language!="")
        return request.option_language;
   if(request.option_language=="")
        return get_language_from_filename(filename);

   return "";
}
