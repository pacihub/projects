SELECT AVG(ratings.rating) FROM ratings 
JOIN movies ON ratings.movie_id = movies.id /* connect the tables based on that */

WHERE movies.year = "2012"