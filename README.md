
 FastPagination     
 
 FastPagination class     
  
 @package  OpenGallery   http://github.com/par7133     
 @author   Daniele Bonini <code@gaox.io>      
 @version  1.0     
 @phpver   5.6 to 7.3      
 @access   public     
 @note The class rendering the output controls is making use of Bootstrap.     
 Furthermore, FastPagination is making use of the class FastErr part of OpenGallery     
 and developed by me http://github/par7133     
 
 Given a div container 'pagination-row', a $cssClass 'pagination' and a $cssClassActivePage named 'active'      
 an example of css customization could be the following:     
 
 .pagination-row {     
   display: table;      
   content: ' ';      
   width:100%;     
   padding-right: 12%;     
 }    
  .pagination {    
    float:right;    
 }    
 .pagination > .active > a {    
    background: #3366CC;    
    font-weight: 400;    
 }    
 .pagination > .active > a:focus {    
    background: #0D62AA;    
    color: white;    
 }    
 .pagination > .active > a:hover {    
   background: #0D62AA;    
   cursor: pointer;    
   color: white;    
 }    
 .pagination > li > a {    
   color: #677a85;    
   font-size: 17px;    
 }    
 .pagination > li > a:hover {    
   color: #677a85;    
 }    
 .pagination > li > a:focus {   
   color: #677a85;    
 }
 
For any need of software additions, plugins and improvements please write to <a href="mailto:info@5mode.com">info@5mode.com</a>  

To help please donate by clicking <a href="https://gaox.io/l/dona1">https://gaox.io/l/dona1</a> and filling the form.  

Feedback: <a href="mailto:code@gaox.io">code@gaox.io</a>
