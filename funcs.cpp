//https://contest.yandex.ru/contest/27883/problems/C/

#include "funcs.h"
#include <bits/stdc++.h>

static const short int Point = 1;
static const short int LineEnd = 2;
typedef short int EventType;

void parseFile(std::istream & input, std::ostream & output){

    unsigned long nPoints;
    int d;
    input >> nPoints >> d;

    //! @brief coordinate, eventType, point index
    std::vector<std::tuple<int,EventType,int>> events(nPoints*2);
    std::vector<int> points(nPoints);

    int pos;
    for(unsigned long i = 0; i<nPoints; ++i){
        input >> pos;
        events[i*2] = {pos, Point, i};
        events[i*2 + 1] = {pos + d, LineEnd, i};
    }

    std::sort(events.begin(), events.end());

    std::set<int> availableTickets;
    for(unsigned long i = 1; i <= nPoints; ++i){
        availableTickets.insert(i);
    }
    int maxTicket = 0;
    for(const auto & event : events){
        switch(std::get<1>(event)){
            case Point:{
                points[std::get<2>(event)] = *availableTickets.begin();
                maxTicket = std::max(maxTicket,*availableTickets.begin());
                availableTickets.erase(availableTickets.begin());
                break;
            }
            case LineEnd:{
                availableTickets.insert(points[std::get<2>(event)]);
                break;
            }
        }
    }
    output << maxTicket << '\n';
    std::copy(points.begin(), points.end(), std::ostream_iterator<int>(output, " "));
}
