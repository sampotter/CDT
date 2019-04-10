/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef CDT_Zahj4kpHLwFgkKtcOI1i
#define CDT_Zahj4kpHLwFgkKtcOI1i

#include "CDT.h"
#include <boost/foreach.hpp>

namespace CDT
{

template <typename T>
inline bool verifyTopology(const CDT::Triangulation<T>& cdt)
{
    // Check if vertices' adjacent triangles contain vertex
    for(VertInd iV(0); iV < VertInd(cdt.vertices.size()); ++iV)
    {
        const Vertex<T>& v = cdt.vertices[iV];
        BOOST_FOREACH(const TriInd iT, v.triangles)
        {
            const std::array<VertInd, 3>& vv = cdt.triangles[iT].vertices;
            if(std::find(vv.begin(), vv.end(), iV) == vv.end())
                return false;
        }
    }
    // Check if triangle neighbor links are fine
    for(TriInd iT(0); iT < TriInd(cdt.triangles.size()); ++iT)
    {
        const Triangle& t = cdt.triangles[iT];
        BOOST_FOREACH(const TriInd iTn, t.neighbors)
        {
            if(iTn == noNeighbor)
                continue;
            const std::array<TriInd, 3>& nn = cdt.triangles[iTn].neighbors;
            if(std::find(nn.begin(), nn.end(), iT) == nn.end())
                return false;
        }
    }
    // Check if triangle's vertices have triangle as adjacent
    for(TriInd iT(0); iT < TriInd(cdt.triangles.size()); ++iT)
    {
        const Triangle& t = cdt.triangles[iT];
        BOOST_FOREACH(const VertInd iV, t.vertices)
        {
            const std::vector<TriInd>& tt = cdt.vertices[iV].triangles;
            if(std::find(tt.begin(), tt.end(), iT) == tt.end())
                return false;
        }
    }
    return true;
}

} // namespace CDT

#endif