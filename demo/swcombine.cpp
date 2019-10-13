// This file is part of liboauth2cpp.
//
// liboauth2cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// liboauth2cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with liboauth2cpp.  If not, see <https://www.gnu.org/licenses/>.

#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <OAuth2.h>

#include "json.hpp"

nlohmann::json returnedJson;

static size_t writeTokens(void *buffer, size_t size, size_t nmemb, void *userp) {
	const char* serializedData(reinterpret_cast<char *>(buffer));
    nlohmann::json *jsonData(reinterpret_cast<nlohmann::json *>(userp));

    *jsonData = nlohmann::json::parse(serializedData);

	return size * nmemb;
}

static size_t getRemoteResource(void *buffer, size_t size, size_t nmemb, void *userp) {
	const char* serializedData(reinterpret_cast<char *>(buffer));
    nlohmann::json *jsonData(reinterpret_cast<nlohmann::json *>(userp));

    *jsonData = nlohmann::json::parse(serializedData);

	return size * nmemb;
}

static std::pair<std::string, std::string> getTokens(oauth2::OAuth2 const& manager) {
	curl_global_init(CURL_GLOBAL_ALL);
    std::pair<std::string, std::string> tokens("", "");

	CURL *curl(curl_easy_init());
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.swcombine.com/ws/oauth2/token/");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeTokens);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnedJson);

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Expect:");
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Transfer-Encoding: chunked");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		std::string postFields(manager.getTokenRequestPostFields());

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

		CURLcode result(curl_easy_perform(curl));
		if (CURLE_OK != result) {
			std::cerr << "curl call failed: " << curl_easy_strerror(result) << std::endl;
		}

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

    if ((returnedJson.find("access_token") != returnedJson.end()) &&
        (returnedJson.find("refresh_token") != returnedJson.end())) {
        tokens.first = returnedJson["access_token"];
        tokens.second = returnedJson["refresh_token"];
    }

	return tokens;
}

static nlohmann::json getResourceFromString(std::string const& resourceURL) {
    nlohmann::json resourceData;
    curl_global_init(CURL_GLOBAL_ALL);

    std::cout << resourceURL << std::endl;
    CURL *curl(curl_easy_init());
	if (curl) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, resourceURL);
		//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getRemoteResource);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resourceData);

        CURLcode result(curl_easy_perform(curl));
		if (CURLE_OK != result) {
			std::cerr << "curl call failed: " << curl_easy_strerror(result) << std::endl;
		}

		curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return resourceData;
}

int main(int argc, char** argv) {
    std::cout << "SWCombine OAuth2 demo using liboauth2cpp" << std::endl;

    auto const clientId("edb5990a11990f523331dd3766806ac8511625de");
    auto const clientSecret("c772fada168cf595e3a34ba48406d5c49e630990");
    auto const endpoint("https://www.swcombine.com/ws/oauth2/auth/");
    auto const scope("CHARACTER_ALL");

    oauth2::OAuth2 oauth2Manager(clientId, clientSecret);
    auto const authorizationURL(oauth2Manager.generateAuthorizationURL(endpoint, scope));

    std::cout << "Please visit the following URL to continue:" << std::endl;
    std::cout << authorizationURL << std::endl;

    std::string authorizationCode;
    std::cout << "Enter the code granted:" << std::endl;
    std::cin >> authorizationCode;
    oauth2Manager.setAuthorizationCode(authorizationCode);

    auto const oauth2Tokens(getTokens(oauth2Manager));

    oauth2Manager.setAccessToken(oauth2Tokens.first);
    //oauth2Manager.setRefreshToken(oauth2Tokens.second);

    std::cout << oauth2Tokens.first << std::endl;
    std::string const resourceEndpoint("http://www.swcombine.com/ws/v1.0/helloauth/");
    auto const getCharacterURL(oauth2Manager.generateResourceURL(resourceEndpoint));

    auto const characterInfo(getResourceFromString(getCharacterURL));
    std::cout << characterInfo << std::endl;;

    return 0;
}
