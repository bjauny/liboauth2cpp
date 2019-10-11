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

#include <iostream>
#include "include/OAuth2.h"

using namespace oauth2;

OAuth2::OAuth2(std::string const& clientId, std::string const& clientSecret) :
    m_clientId(clientId),
    m_clientSecret(clientSecret),
    m_redirectUri("urn:ietf:wg:oauth:2.0:oob"),
    m_authorizationCode("") {
}

std::string OAuth2::generateAuthorizationURL(std::string const& endpoint, std::string const& requestedScope) const {
    std::string fullURL(endpoint);

    fullURL += "?client_id=" + m_clientId;
    fullURL += "&response_type=code";
    fullURL += "&redirect_uri=" + m_redirectUri;
    fullURL += "&scope=" + requestedScope;
    fullURL += "&access_type=offline";

    return fullURL;
}
