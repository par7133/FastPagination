<?php

/**
 * Copyright (c) 2016, 2022, the Open Gallery's contributors
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither Open Gallery nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * class.fastpagination.inc
 * 
 * FastPagination class.
 * 
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2016, 2022, the Open Gallery's contributors     
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

namespace OpenGallery\OpenGallery;

/**
 * FastPagination
 *
 * FastPagination class
 *
 * @package  OpenGallery   http://github.com/par7133
 * @author   Daniele Bonini <my25mb@aol.com>
 * @version  1.0
 * @access   public
 * @note The class rendering the output controls is making use of Bootstrap.
 * Furthermore, FastPagination is making use of the class FastErr part of OpenGallery
 * and developed by me http://github/par7133
 * 
 * Given a div contain 'pagination-row', a $cssClass 'pagination' and  $cssClassActivePage 'active' 
 * an example of css customization could be the following:
 * 
 *.pagination-row {
 *  display: table; 
 *  content: ' '; 
 *  width:100%; 
 *  padding-right: 12%;
 *}
 * .pagination {
 *   float:right;
 *}
 *.pagination > .active > a {
 *   background: #3366CC;
 *   font-weight: 400;
 *}
 *.pagination > .active > a:focus {
 *   background: #0D62AA;
 *   color: white;
 *}
 *.pagination > .active > a:hover {
 *  background: #0D62AA;
 *  cursor: pointer;
 *  color: white;
 *}
 *.pagination > li > a {
 *  color: #677a85;
 *  font-size: 17px;
 *}
 *.pagination > li > a:hover {
 *  color: #677a85;
 *}
 *.pagination > li > a:focus {
 *  color: #677a85;
 *}
 */
class FastPagination 
{
  /**
   * The css class of a non-active page <li>
   *
   * @access private
   * @var string;
   */  
  private $cssClass = "";

  /**
   * The css class of an active page <li>
   *
   * @access private
   * @var string
   */  
  private $cssClassActivePage = "";  

  /**
   * the current page
   *
   * @access private
   * @var string
   */  
  private $currentPage;

  /**
   * The number of records per page
   *
   * @access private
   * @var integer
   */  
  private $itemsPerPage;

  /**
   * The landing page of a page link
   *
   * @access private
   * @var string
   */  
  private $landingPage;

  /**
   * The landing page query string of a page link
   *
   * @access private
   * @var string
   */  
  private $landingPageQueryString = "xf=1";
  
  /**
   * the max visible pages of the pagination control
   *
   * @access private
   * @var integer
   */  
  private $maxVisiblePages = 3;

  /**
   * The current starting pages of the pagination control
   *
   * @access private
   * @var integer
   */  
  private $startingPage;

  /**
   * The title of a page ctrl
   *
   * @access private
   * @var string
   */  
  private $titlePage = "";  

  /**
   * The title of the beginning ctrl
   *
   * @access private
   * @var string
   */  
  private $titleBeginning = "";   

  /**
   * The title of the end ctrl
   *
   * @access private
   * @var string
   */  
  private $titleEnd = "";
  
  /**
   * The total number of records in the scope
   *
   * @access private
   * @var integer
   */  
  private $totItems;

  /**
   * The total number of pages in the scope
   *
   * @access private
   * @var integer
   */  
  private $totPages;
  
  /**
   * The default constructor of the object
   *
   * @return void
   * @access public
   */   
  public function __construct() 
  {
  }

  /**
   * Set the css class for the pagination control <ul>
   *
   * @param  string  $cssClass the css class   
   * @return void
   * @access public
   */  
  public function setCssClass($cssClass) 
  {
    $this->cssClass = $cssClass;
  }
  
  /**
   * Set the css class for the active page <li>
   *
   * @param  string  $cssClass the css class   
   * @return void
   * @access public
   */  
  public function setCssClassActivePage($cssClass) 
  {
    $this->cssClassActivePage = $cssClass;
  }

  /**
   * Set the current page
   *
   * @param  integer  $currentPage the current page   
   * @return void
   * @access public
   */
  public function setCurrentPage($currentPage) 
  {
    if (!is_numeric($currentPage)) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: invalid currentPage value: ". $currentPage, __FILE__, __LINE__);
    }
    $this->currentPage = $currentPage;
  }
  
  /**
   * Set the max visible pages of the pagination control
   *
   * @param  integer  $maxVisiblePages the max visible pages   
   * @return void
   * @access public
   */
  public function setMaxVisiblePages($maxVisiblePages) 
  {
    if (!is_numeric($maxVisiblePages)) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: invalid maxVisiblePages value: ". $maxVisiblePages, __FILE__, __LINE__);
    }
    $this->maxVisiblePages = $maxVisiblePages;
  }

  /**
   * Set the number of records per page
   *
   * @param  integer  $itemsPerPage the number of records per page   
   * @return void
   * @access public
   */
  public function setItemsPerPage($itemsPerPage) 
  {
    if (!is_numeric($itemsPerPage) || $itemsPerPage<=0) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: invalid itemsPerPage value: ". $itemsPerPage, __FILE__, __LINE__);
    }
    $this->itemsPerPage = $itemsPerPage;
  }  

  /**
   * Set the landing page of a page link
   *
   * @param  string  $landingPage the landing page   
   * @return void
   * @access public
   */
  public function setLandingPage($landingPage) 
  {
    if (filter_var($landingPage, FILTER_VALIDATE_URL)) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: invalid landing page value: ". $landingPage, __FILE__, __LINE__);
    }
    $this->landingPage = $landingPage;
  }
  
  /**
   * Set the landing page query string of a page link
   *
   * @param  string  $landingPageQueryString the query string   
   * @return void
   * @access public
   */
  public function setLandingPageQueryString($landingPageQueryString) 
  {
    $this->landingPageQueryString = $landingPageQueryString;
  }

  /**
   * Set the title for a page ctrl
   *
   * @param  string  $titlePage the title   
   * @return void
   * @access public
   */
  public function setTitlePage($titlePage) 
  {
    $this->titlePage = $titlePage;
  }

  /**
   * Set the title for the beginning ctrl
   *
   * @param  string  $titleBeginning the title   
   * @return void
   * @access public
   */
  public function setTitleBeginning($titleBeginning) 
  {
    $this->titleBeginning = $titleBeginning;
  }  
 
 /**
   * Set the title for the end ctrl
   *
   * @param  string  $titleEnd the title   
   * @return void
   * @access public
   */
  public function setTitleEnd($titleEnd) 
  {
    $this->titleEnd = $titleEnd;
  }    
  
  /**
   * Set the total number of records in the scope
   *
   * @param  integer  $totItems the total number of records   
   * @return void
   * @access public
   */
  public function setTotItems($totItems) 
  {
    if (!is_numeric($totItems) || $totItems<0) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: invalid totItems value: ". $totItems, __FILE__, __LINE__);
    }
    $this->totItems = $totItems;
  }  

  /**
   * Calculate the total pages in the scope
   *
   * @return void
   * @access private
   */
  private function calcTotPages() 
  {
    if ($this->totItems > 0) {
      $this->totPages = intdiv_1($this->totItems, $this->itemsPerPage);
      if (($this->totItems % $this->itemsPerPage)>0) { 
        $this->totPages = $this->totPages + 1;
      }
    } else {
      $this->totPages = 0;
    }
  }  
  
  /**
   * Calculate the starting page
   *
   * @return void
   * @access private
   */
  private function calcStartPage() 
  {
    if ($this->currentPage<=$this->maxVisiblePages) {
      $this->startingPage = 1;
    } else {  
      if (($this->currentPage + $this->maxVisiblePages -1)>=$this->totPages) {
        $this->startingPage = $this->totPages - ($this->maxVisiblePages - 1);
      } else {
        $this->startingPage = $this->currentPage;
      }
    }
  }

  /**
   * Display the pagination control
   *
   * @return void
   * @access public
   */  
  public function show() 
  {
    $this->checkDataBeforeShow();
    
    $this->calcTotPages();
    
    $this->calcStartPage();
    
    $landingPage = $this->landingPage;
    $cssClass = $this->cssClass;
    $cssClassActivePage = $this->cssClassActivePage;
    $titlePage = $this->titlePage;
    $titleBeginning = $this->titleBeginning;
    $titleEnd = $this->titleEnd;
    $landingPageQueryString = $this->landingPageQueryString;
    
    if ($this->totPages>=1) {
    
      echo "<ul class=\"$cssClass\">";

      if ($this->maxVisiblePages>=1 && $this->totPages>=1) { 
        echo "<li title=\"" . $titleBeginning . "\"><a href=\"$landingPage?$landingPageQueryString" . "&page=1" . "\" style=\"cursor:pointer;\">&nbsp;<span class='glyphicon glyphicon-fast-backward' style='position: relative; top: +3px;'></span>&nbsp;</a></li>"; 
      }

      if ($this->currentPage>=($this->maxVisiblePages+1)) { 
        echo "<li title=\"" . $titlePage . "\"><a href=\"$landingPage?$landingPageQueryString" . "&page=" . urlencode($this->startingPage-1) . "\" style=\"cursor:pointer\">...</a></li>"; 
      }

      for ($i=$this->startingPage; $i<=($this->startingPage + $this->maxVisiblePages - 1); $i++) {
        if ($i > $this->totPages) {
           break;
        }
        if ($i==$this->currentPage) { 
          echo "<li class=\"$cssClassActivePage\" title=\"" . $titlePage . "\"><a href=\"$landingPage?$landingPageQueryString&page=" . urlencode($i) . "\" style=\"cursor:pointer\">$i</a></li>";
        } else {
          echo "<li title=\"" . $titlePage . "\"><a href=\"$landingPage?$landingPageQueryString&page=" . urlencode($i) . "\" style=\"cursor:pointer\">$i</a></li>";
        }	   
      }

      if ($this->totPages > ($this->startingPage + $this->maxVisiblePages - 1)) {
        echo "<li title=\"" . $titlePage . "\"><a href=\"$landingPage?$landingPageQueryString&page=" . urlencode($this->startingPage + $this->maxVisiblePages) . "\" style=\"cursor:pointer\">...</a></li>";	
      }

      if ($this->totPages>=1) { 
        echo "<li title=\"" . $titleEnd . "\"><a href=\"$landingPage?$landingPageQueryString" . "&page=" . $this->totPages . "\" style=\"cursor:pointer;\">&nbsp;<span class='glyphicon glyphicon-fast-forward' style='position: relative; top: +3px;'></span>&nbsp;</a></li>"; 
      }

      echo "</ul>";
    }  
  }

  /**
   * Check the data before to show the control
   *
   * @return void
   * @access private
   */    
  private function checkDataBeforeShow() 
  {
    if (!isset($this->cssClass)) {
      $this->cssClass = "pagination";
    }
    if (!isset($this->cssClassActivePage)) {
      $this->cssClassActivePage = "active";
    }
    if (!isset($this->currentPage)) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: currentPage not specified. ", __FILE__, __LINE__);
    }
  
    if (!isset($this->itemsPerPage)) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: itemsPerPage not specified. ", __FILE__, __LINE__);
    }

    if (!isset($this->landingPage)) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: landingPage not specified. ", __FILE__, __LINE__);
    }

    if (!isset($this->totItems)) {
      FastErr::trigger_error1(ERR::ERR_GENERAL, "Pagination: totItems not specified. ", __FILE__, __LINE__);
    }
  }
}
