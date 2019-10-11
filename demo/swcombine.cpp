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
#include <OAuth2.h>

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

    return 0;
}
