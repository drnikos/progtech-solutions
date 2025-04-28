#include <bits/stdc++.h>
using namespace std;

class TopGenres
{
public:
    TopGenres();
    ~TopGenres();
    void insert_vote(const string &title, int vote);
    void insert_movie(const string &title, const string &genre);
    void print(int howmany);

private:
    map<string, string> movie_genres;
    map<string, pair<int, int>> genres_votes;
};

TopGenres::TopGenres() {}
TopGenres::~TopGenres() {}
void TopGenres::insert_vote(const string &title, int vote)
{
    auto it = movie_genres.find(title);
    if (it != movie_genres.end())
    {
        string genre = it->second;
        auto genre_it = genres_votes.find(genre);
        if (genre_it == genres_votes.end())
        {
            genres_votes[genre] = {1, vote};
        }
        else
        {
            genre_it->second.first++;
            genre_it->second.second += vote;
        }
    }
}
void TopGenres::insert_movie(const string &title, const string &genre)
{
    auto it = movie_genres.find(title);
    if (it == movie_genres.end())
    {
        movie_genres[title] = genre;
    }
    else
    {
        it->second = genre;
    }
}
void TopGenres::print(int howmany)
{
    vector<pair<string, int>> genreVotes;
    for (auto &movie : genres_votes)
    {
        if (movie.second.first > 0)
        {
            // int avgVote = movie.second.second / movie.second.first;
            genreVotes.push_back({movie.first, movie.second.first});
        }
    }
    sort(genreVotes.begin(), genreVotes.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { 
         if (a.second != b.second)
           return a.second > b.second;
         return a.first < b.first; });
    for (int i = 0; i < howmany && i < genreVotes.size(); i++)
    {
        cout << genreVotes[i].first << " " << genreVotes[i].second << endl;
    }
}
int main()
{
    int n, g;
    cin >> n >> g;
    string title, person, genre;
    int vote;
    TopGenres list;
    for (int i = 0; i < n; i++)
    {
        cin >> title >> genre;
        list.insert_movie(title, genre);
    }
    while (cin >> title >> person >> vote)
    {
        if (vote >= 0 && vote <= 100)
            list.insert_vote(title, vote);
    }
    list.print(g);
}