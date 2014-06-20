/* $Id */

-- SUMMARY --

The book top navbar module takes the navigation bar that appears
at the bottom of each book page, and repeats it at the top of the page.
This can be especially useful for users who are scanning a book, looking
for something they have seen before.

You can specify whether the table of contents is shown in the top navigation
bar. You can also specify how long a page must be before the navigation
bar is added. Repeated navigation can look strange on short pages.


-- REQUIREMENTS --

The book module must be enabled.


-- INSTALLATION --

Install as usual. eee http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

Go to admin/config/user-interface/book-top-navbar to configure. 
Set the minimum number of characters of content that must be present 
before the top navigation appears. You can also choose whether the 
table of contents is shown or not.
