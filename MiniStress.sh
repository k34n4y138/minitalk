#!/bin/bash
for i in {1..2500}
do
	echo ----begin----
	SERVERID=$(top -l 1 | grep server | grep $USER | awk '{print $1}')
	time ./client $SERVERID  "۞۞Et harum quidem rerum facilis est et expedita 📗📗📗distinctio.  Nam libero tempore, cum soluta nobis est eligendi optio cumque  nihil impedit quo minus id quod maxime placeat facere possimus,  omnis voluptas assumenda est, omnis dolor repellendus. Temporibus  autem quibusdam et aut officiis debitis aut rerum necessitatibus  saepe eveniet ut et voluptates repudiandae sint et molestiae non  recusandae. Itaque earum rerum hic tenetur a sapiente delectus, ut aut  reiciendis voluptatibus maiores alias consequatur aut perferendis doloribus  asperiores repellat.📗Et harum quidem rerum facilis est et expedita distinctio.  Nam libero tempore, cum soluta nobis est eligendi optio cumque  nihil impedit quo minus id quod maxime placeat facere possimus,  omnis voluptas assumenda est, omnis dolor repellendus. Temporibus  autem quibusdam et aut officiis debitis aut rerum necessitatibus  saepe eveniet ut et voluptates repudiandae sint et molestiae non  recusandae. Itaque earum rerum hic tenetur a sapiente delectus📗📗📗📗📗📗📗f📗📗📗📗📗📗📗📗📗 ە ܫ ە📗📗"
	sleep 1
done