
// Heading
let webpageHeading = document.createElement('h1');
let wepageHeadingText = document.createTextNode('Curriculum Vitae');
let body = document.body;
webpageHeading.appendChild(wepageHeadingText);
body.appendChild(webpageHeading);

// Summary Statement
let summaryStatementHeading = document.createElement('h2');
let summaryStatementText = document.createTextNode('Summary Statement');
summaryStatementHeading.appendChild(summaryStatementText);
body.appendChild(summaryStatementHeading);

let SummaryStatementContent = document.createElement('p');
let summaryStatementContentText = document.createTextNode('The quality that makes me unique is grasping concepts and gaining a solid understanding of any new topic, environment, or situation. My method of thinking is very chronological and yet quite creative. I can pay acute attention to details which allows me to systematically plan and understand complex topics and apply my problem-solving skills in an innovative fashion. Experienced and exposed in creating many projects of different genres, such as the arts and the sciences, allows me to think out-of-the-box to solve any given problem. I have a sophisticated technical skillset due to my lifetime experience of distributed computing that has allowed me to gain a better understanding of technology and the importance of its reliability!');
SummaryStatementContent.appendChild(summaryStatementContentText);
body.appendChild(SummaryStatementContent);

// CSS
let allH1s = document.querySelectorAll('h1');
for(let i of allH1s) { i.style = "font: bold;font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;color: #000B4F;text-align: center;margin-top: 100px;"}

let allH2s = document.querySelectorAll('h2');
for(let i of allH2s) { i.style = "font: bold;font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;color: indigo;text-align: center;margin-top: 30px;"}

let allPs = document.querySelectorAll('p');
for(let i of allPs) { i.style = "font-style: normal;font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;text-align: justify;margin-top: 10px;margin-left: 30%;margin-right: 30%;"}

body.style = "background-color: #d5e1df;";

let resumeData = [
    {
        'title': 'Summary Statement',
        'subtitle': '',
        'details': '',
        'description': 'The quality that makes me unique is grasping concepts and gaining a solid understanding of any new topic, environment, or situation. My method of thinking is very chronological and yet quite creative. I can pay acute attention to details which allows me to systematically plan and understand complex topics and apply my problem-solving skills in an innovative fashion. Experienced and exposed in creating many projects of different genres, such as the arts and the sciences, allows me to think out-of-the-box to solve any given problem. I have a sophisticated technical skillset due to my lifetime experience of distributed computing that has allowed me to gain a better understanding of technology and the importance of its reliability!',
    },
    {
        'title': 'Work Experience',
        'subtitle': 'Software Test Engineer at Collins Aerospace',
        'details': 'May 2021 - August 2021',
        'description': 'The quality that makes me unique is grasping concepts and gaining a solid understanding of any new topic, environment, or situation. My method of thinking is very chronological and yet quite creative. I can pay acute attention to details which allows me to systematically plan and understand complex topics and apply my problem-solving skills in an innovative fashion. Experienced and exposed in creating many projects of different genres, such as the arts and the sciences, allows me to think out-of-the-box to solve any given problem. I have a sophisticated technical skillset due to my lifetime experience of distributed computing that has allowed me to gain a better understanding of technology and the importance of its reliability!',
    },
    {
        'title': 'Summary Statement',
        'subtitle': '',
        'details': '',
        'description': 'The quality that makes me unique is grasping concepts and gaining a solid understanding of any new topic, environment, or situation. My method of thinking is very chronological and yet quite creative. I can pay acute attention to details which allows me to systematically plan and understand complex topics and apply my problem-solving skills in an innovative fashion. Experienced and exposed in creating many projects of different genres, such as the arts and the sciences, allows me to think out-of-the-box to solve any given problem. I have a sophisticated technical skillset due to my lifetime experience of distributed computing that has allowed me to gain a better understanding of technology and the importance of its reliability!',
    },
    {
        'title': 'Summary Statement',
        'subtitle': '',
        'details': '',
        'description': 'The quality that makes me unique is grasping concepts and gaining a solid understanding of any new topic, environment, or situation. My method of thinking is very chronological and yet quite creative. I can pay acute attention to details which allows me to systematically plan and understand complex topics and apply my problem-solving skills in an innovative fashion. Experienced and exposed in creating many projects of different genres, such as the arts and the sciences, allows me to think out-of-the-box to solve any given problem. I have a sophisticated technical skillset due to my lifetime experience of distributed computing that has allowed me to gain a better understanding of technology and the importance of its reliability!',
    },

];