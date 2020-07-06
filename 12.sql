SELECT title from movies, people, stars

WHERE movies.id = stars.movie_id and people.id = stars.person_id and people.name = "Johnny Depp" 


INTERSECT

SELECT title from movies, people, stars
WHERE movies.id = stars.movie_id and people.id = stars.person_id and people.name = "Helena Bonham Carter";

