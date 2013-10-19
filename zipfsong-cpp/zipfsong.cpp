#include <iostream>
#include <map>
#include <algorithm>
#include <queue>

#include <stdio.h>

struct Song
{
public:
    Song(std::string name, long long int f, int index) :
        name_(name), f_(f), index_(index) {}

public:
    std::string name_;
    unsigned long long int f_;
    unsigned int index_;
};

static bool
song_less(const Song& s1, const Song& s2)
{
    if (s1.f_ == s2.f_)
        return s1.index_ < s2.index_;
    else
        return s2.f_ < s1.f_;
}

int
main(void)
{
    unsigned int n, m;
    std::string line;
    std::priority_queue<Song, std::vector<Song>,
    bool (&)(const Song&, const Song&)> PQ(song_less);
    std::vector<Song> songs;

    std::cin >> n >> m;
    getline(std::cin, line);

    for (unsigned int i = 0; i < n; i++) {
        long long int f;
        std::string name;

        std::cin >> f >> name;
        f *= (i+1);

        PQ.push(Song(name, f, i));
        if (PQ.size() > m)
            PQ.pop();
    }

    while (!PQ.empty()) {
        songs.push_back(PQ.top());
        PQ.pop();
    }

    for (std::vector<Song>::const_reverse_iterator it = songs.rbegin();
        it != songs.rend(); ++it) {
        printf("%s\n", (*it).name_.c_str());
    }

    return 0;
}
