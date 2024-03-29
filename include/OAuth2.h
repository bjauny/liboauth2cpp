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

#ifndef _OAUTH2_H_
#define _OAUTH2_H_

#include <map>
#include <string>

namespace oauth2 {

class OAuth2 {
private:
    std::string m_clientId;
    std::string m_clientSecret;
    std::string m_redirectUri;
    std::string m_authorizationCode;

public:
    OAuth2(std::string const& clientId, std::string const& clientSecret);

    std::string generateAuthorizationURL(std::string const& endpoint, std::string const& requestedScope) const;
    // void setAuthorizationCode(std::string const& code) {m_authorizationCode = code;}
    // std::pair<std::string const&, std::string const&> getTokens(void) const;
    // void getResource(std::string const& endpoint) const;
};

}

#endif // _OAUTH2_H_
