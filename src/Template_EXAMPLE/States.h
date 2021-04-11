#pragma once
#include <map>
#include <set>
#include <string>
#include <list>
#include <initializer_list>

enum State { // множество состояний
    MAIN,
    MAIN_A,
    MAIN_B,
    C,
    C_A,
    ERROR,
    EMPTY_STR,
    FILE_END
};

enum Bracket {
    OPEN, 
    CLOSE
};

template <typename T>
class setWrapper {
    std::set<T> curSet;

public:
    setWrapper(std::list<T> list) {
        for(auto &it : list) {
            curSet.insert(it);
        }
    }

    std::set<T> getSet(){
        return curSet;
    }
};

template <class T, class P>
class mapWrapper {
    std::map<T, P> curMap;
public:
    mapWrapper(const std::list< std::pair<T, P> > list) {

        for(auto it = list.begin(); it != list.end(); it++) {
            curMap[it->first] = it->second;
        }
    }

    std::map<T, P> getMap() {
        return curMap;
    }
};

typedef std::set<State> setOfState;
typedef std::set<std::string> setOfStr;
typedef std::map<State, setOfStr> mapStateSetStr;
typedef std::map<State, mapStateSetStr> mapTransition;

std::map<State, State> startStates = mapWrapper<State, State>( {
                                                    {MAIN, MAIN_A},
                                                    {C, C_A}
                                    }).getMap();

std::map<State, setOfState > endStates = mapWrapper<State, setOfState>({
                                        {MAIN,  setWrapper<State>( {MAIN_B, C}).getSet()},
                                        {C,     setWrapper<State>( {C_A} ).getSet()}
                                       }).getMap();

mapTransition _main = mapWrapper<State, mapStateSetStr>({
                                    {
                                        MAIN_A, mapWrapper<State, setOfStr>({
                                            {
                                                MAIN_A, setWrapper<std::string>(
                                                    {
                                                        "a"
                                                    }
                                                ).getSet()
                                            },

                                            {
                                                MAIN_B, setWrapper<std::string>(
                                                    {
                                                        "b"
                                                    }
                                                ).getSet()
                                            }
                                        }).getMap()
                                    },

                                    {
                                        MAIN_B, mapWrapper<State, setOfStr>({
                                            {
                                                MAIN_B, setWrapper<std::string>(
                                                    {
                                                        "b"
                                                    }
                                                ).getSet()
                                            },

                                            {
                                                C, setWrapper<std::string>(
                                                    {
                                                        "c"
                                                    }
                                                ).getSet()
                                            },
                                        }).getMap()
                                    },

                                    {
                                        C, mapWrapper<State, setOfStr>({
                                            {
                                                MAIN_B, setWrapper<std::string>(
                                                    {
                                                        "b"
                                                    }
                                                ).getSet()
                                            }
                                        }).getMap()
                                    }
                                }).getMap();

mapTransition _c = mapWrapper<State, mapStateSetStr>({
                                    {
                                        C_A, mapWrapper<State, setOfStr>({
                                            {
                                                C_A, setWrapper<std::string>(
                                                    {
                                                        "c"
                                                    }
                                                ).getSet()
                                            }
                                        }).getMap()
                                    }
                                }).getMap();

std::map<State, mapTransition> mapGraph= mapWrapper<State, mapTransition>({
                                        {MAIN, _main},
                                        {C, _c}
                                        }).getMap();

std::set<State> graphs = setWrapper<State>({
                            MAIN, 
                            C
                            }).getSet();

typedef std::map <State, std::string> mapMark;

mapMark _MAIN_A = mapWrapper<State, std::string>({
                    {MAIN_A, "["},
                    {MAIN_B, "]"}
                }).getMap();

mapMark _MAIN_B = mapWrapper<State, std::string>({
                    {MAIN_B, "]"}
                }).getMap();

std::map<State, mapMark> marks = mapWrapper<State, mapMark>({
                                 {MAIN_A, _MAIN_A},
                                 {MAIN_B, _MAIN_B}
                                 }).getMap();

           
class Mark {
    Bracket bracket;  
    std::string id;

public:
    Mark(Bracket bracket, const char* str) {
        this->bracket = bracket;
        this->id = std::string(str);
    };

    Mark(const Mark& mark) {
        bracket = mark.bracket;
        id = mark.id;
    }

    const Mark& operator= (const Mark& mark) {
        if (this == &mark)
        return *this;

        this->bracket = mark.bracket;
        this->id = mark.id;

        return *this;
    }
};

Mark p_1(OPEN, "a");
Mark p_2(OPEN, "b");

std::pair<State, Mark> keys(MAIN, p_1);
std::pair<State, Mark> keys_test(MAIN, Mark(OPEN, "c"));

// std::map<State, Mark> test = mapWrapper<State, Mark>({
//                              {MAIN, popka}
                            
//                              }).getMap();




