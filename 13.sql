SELECT name from people
JOIN stars on stars.person_id = people.id 
WHERE name != "Kevin Bacon"
AND movie_id IN (SELECT movie_id FROM people
JOIN stars ON stars.person_id = people.id
WHERE name = "Kevin Bacon" and birth = 1958)
