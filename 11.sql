SELECT title from movies

JOIN people ON people.id = stars.person_id
JOIN stars ON movies.id = stars.movie_id
JOIN ratings ON movies.id = ratings.movie_id

WHERE people.name = "Chadwick Boseman"

ORDER BY rating DESC LIMIT 5;