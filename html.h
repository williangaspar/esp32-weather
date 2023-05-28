#ifndef HTML_H
#define HTML_H

namespace HTML {
const char homePage[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html lang='en'>
   <head>
   <meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=no'>
   <title>ESP32 Weather</title>
   </head>
   <body>
   <div id='main-div' class='main-div'>
   <h2>Search and select city</h2>
   <input type='text' placeholder='Search city' id='city-input' 
   onkeyup='onSearchType()' 
   />
   <div id='cityDropdown' class='dropdown-content'></div>
   <div class="loader" id='loader'></div>
   </div>
   </body>
   <style>
   body { 
   background-color: #eee; 
   display: flex; 
   flex-direction: column;  align-items: center; 
   font-family: Arial, Helvetica, sans-serif; 
   color: #555;  
   } 

   .main-div { 
   background-color: white; 
   border-radius: 5px; 
   padding: 20px; 
   padding-top: 0px; 
   margin-top: 20px; 
   display: flex; 
   min-width: 300px; 
   flex-direction: column; 
   } 

   .dropdown-content { 
   background-color: #f6f6f6; 
   overflow: auto; 
   border: 1px solid #ddd; 
   z-index: 1;  
   display: none;
   } 

   .dropdown-content a { 
   color: black; 
   padding: 12px 12px; 
   text-decoration: none; 
   display: block; 
   cursor: pointer; 
   } 

   .dropdown-content a:hover { 
   background-color: #fff; 
   } 

   input { 
   border: solid 1px #eee; 
   padding: 5px; 
   display: flex; 
   } 
   
   .loader {
   border: 6px solid #f3f3f3;
   border-radius: 50%;
   align-self: center;
   margin-top: 10px;
   border-top: 6px solid #3498db;
   width: 20px;
   height: 20px;
   -webkit-animation: spin 1s linear infinite; /* Safari */
   animation: spin 1s linear infinite;
   display: none;
   }

   /* Safari */
   @-webkit-keyframes spin {
   0% { -webkit-transform: rotate(0deg); }
   100% { -webkit-transform: rotate(360deg); }
   }

   @keyframes spin {
   0% { transform: rotate(0deg); }
   100% { transform: rotate(360deg); }
   }
   </style>

   <script>
   let doSearch = false; 
   let timeoutId = null; 
   
   function onSearchType() { 
   clearTimeout(timeoutId); 
   timeoutId = setTimeout(searchCity, 2000); 
   } 

   async function searchCity(file) { 
   const cityName = document.getElementById('city-input').value; 
   if(cityName) {
   document.getElementById('loader').style.display = 'block';
   
   const result = await fetch('/cities/get/' + cityName); 
   const data = await result.json(); 
   createList(data.results); 
   }
   } 

   function createList(results) { 
   document.getElementById('loader').style.display = 'none';
   document.getElementById('cityDropdown').innerHTML = null;
   
   if (results) {
   document.getElementById('cityDropdown').style.display='block';
   }
   
   results.forEach((data) =>{ 
   const newItem = document.createElement('a'); 
   newItem.innerHTML = data.name +
   (data.admin1 ? ' - ' + data.admin1 : '')  +
   ' - ' + data.country; 
   newItem.href = '/cities/set/'+ data.name + '/' + data.latitude + '/' +  
   data.longitude; 
   newItem.onclick = () => {
   document.getElementById('cityDropdown').style.display='none';
   document.getElementById('loader').style.display = 'block';

   };
   document.getElementById('cityDropdown').appendChild(newItem); 
   }); 
   } 
   </script>
   </html>
   )rawliteral";

const char allSet[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html lang='en'>
  <head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=no'>
  <title>ESP32 Weather</title>
  </head>
  <body>
  <h1> All set !</ h1>
  </body>
  <style>
  body { 
  background-color: #eee; 
  display: flex; 
  flex-direction: column;  align-items: center; 
  font-family: Arial, Helvetica, sans-serif; 
  color: #555;  
  } 
  </ style>
  </ html>;
  )rawliteral";

}  // namespace HTML
#endif
