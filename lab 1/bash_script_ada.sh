#!/bin/bash
echo "Sear for packets"
echo "Script by Andreevsckih Dariya"
echo "This script search for intalled packet on your PC."
echo "If searched packet isn't installed you will have opporuinity to do it."
contin=true
while [ $contin ]
do
	echo "Please, packet's name for searching:"
	read packet_name
if [ "$packet_name" = "" ]
then
	echo"Error! Can't search with no name" >$2
else
	if rpm -qa| grep "$packet_name"
	then
		rpm -qi "$packet_name"
	else
		echo "No such packet on this PC."
		echo "Start serching for $packet_name"
		if yum search "$packet_name"
		then
			echo "Succes searching! Would you like to install $packet_name? [y/n]"
			read user_answer
			if  [ "$user_answer" = "y" ]
			then
				yum install "$packet_name"
				echo "Install succed"
			elif [ "$user_answer" = "n" ] 
			then
				echo "Installation is cancelled"
			else
				echo "Error! Unrecognized command" >$2
			fi
		else
		echo "Sorry, packet with such file was not found. Try different name"
		fi
	fi
fi
echo "Would you like to quit search? [y/n]"
read user_answer
        if  [ "$user_answer" = "y" ]
        then
        	break
		contin=false		
        elif [ "$user_answer" = "n" ]
        then
		contin=true
        else
		echo "Error! Unrecognized command" >$2
        fi
done
echo "Script stops working"
exit "0"
