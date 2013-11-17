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
song_greater(const Song& s1, const Song& s2)
{
  if (s1.f_ == s2.f_)
    return s1.index_ < s2.index_;
  else
    return s1.f_ > s2.f_;
}

int
main(void)
{
  unsigned int n, m;
  std::string line;

  // Priority queue that holds the m songs with highest quality according to
  // Zipf's Law. The quality is defined as qi = fi/zi where fi is the number
  // of times the song has been played and zi is the number of times that Zipf's
  // law predicts that the song is played.
  std::priority_queue<Song, std::vector<Song>,
    bool (&)(const Song&, const Song&)> PQ(song_greater);

  std::vector<Song> songs;

  std::cin >> n >> m;
  getline(std::cin, line);

  for (unsigned int i = 0; i < n; i++) {
    long long int f;
    std::string name;

    std::cin >> f >> name;
    // qi = fi/zi, zi = 1, 1/2, 1/4, ... 1/i => qi = fi*(i+1)
    long long int q = f*(i+1);

    // Push the new song and pop the song with the lowest quality if the 
    // priority queue contains more than m elements.
    PQ.push(Song(name, q, i));
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
