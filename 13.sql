SELECT * from movies
Where movies.id in (select movies.id from movies 
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE name = "Kevin Bacon" and birth = "1956");