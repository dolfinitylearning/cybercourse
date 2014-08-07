//"use strict";

(function ($) {

/**
 * Copied from text.js (standard Drupal long text field).
 * Auto-hide summary textarea if empty and show hide and unhide links.
 */

Drupal.behaviors.addMathJaxConfig = {
  attach: function (context, settings) {
    MathJax.Hub.Config({
        tex2jax: {
            inlineMath: [['\\(','\\)']],
            displayMath: [ ['$$','$$'], ['\\[','\\]'] ],
            skipTags: ['script', 'noscript', 'style', 'textarea', 'pre'] // removed 'code' entry
      }
    });
    MathJax.Hub.Queue(function() {
        var all = MathJax.Hub.getAllJax(), i;
        for(i = 0; i < all.length; i += 1) {
            all[i].SourceElement().parentNode.className += ' has-jax';
        }
    });
  }
};

})(jQuery);
