# message_cleanser
In the program, the user gives an input of multiple lines containing text and emoticons as well as special character, there is also a separating line ('###'), after which there is an emoticon dictionary.
the program works in 5 stages, in the first stage, the program counts all the tokens in the first line of the message. After the first stage, the user enters the rest of the message. In the second stage, the program removes all the alphanumeric characters from the entire message. The 3rd stage of the program is designed to remove all the leading, trailing and consecutive commas between the emoticons.Stage 4, reads all the message after the separating line, and otputs the longest emoji followed by its length and the total number of emojis in the dictionary.The final stage reads all the emojis in the orignal message and compares them with the emoticon dictionary, if any emoticon is not present in the dictionary, that is it is an invalid emoticon, it is removed from the message and the final clenased message with all the valid emoticons separated by commas is displayed.

Example :
SAMPLE INPUT-
That,was,really,funny,=)),:))
I,have,no,clue,:/,:?,on,this,matter
^-^,You,are,the,best,*-*,:-* 
See,you,|->,bye
Thank,you,:) 
###
:),happy 
:)),happy 
^-^,happy 
:?,confused 
:/,confused 
=)),fun 
:(,sad 
:((,sad 
**_**,love 
:-*,love

SAMPLE OUTPUT-
Stage 1
==========
Number of tokens: 6

Stage 2
==========
,,,,=)),:))
,,,,:/,:?,,,
^-^,,,,,*-*,:-*
,,|->,
,,:)

Stage 3
==========
=)),:))
:/,:?
^-^,*-*,:-*
|->
:)

Stage 4
==========
Emoticon total: 10
Longest: **_**
Length: 5

Stage 5
==========
=)),:))
:/,:?
^-^,,:-*
:)
