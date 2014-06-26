#from __future__ import absolute_import
from docutils import nodes, core, io
from docutils.parsers.rst import Directive, directives
from docutils.parsers.rst.directives.body import *
from docutils.parsers.rst.roles import set_classes
from docutils.utils.code_analyzer import Lexer, LexerError, NumberLines

"""
https://gist.github.com/dbrgn/2922648
ReST directive for embedding Youtube and Vimeo videos.
 
There are two directives added: ``youtube`` and ``vimeo``. The only
argument is the video id of the video to include.
 
Both directives have three optional arguments: ``height``, ``width``
and ``align``. Default height is 281 and default width is 500.
 
Example::
 
.. youtube:: anwy2MPT5RE
:height: 315
:width: 560
:align: left
 
:copyright: (c) 2012 by Danilo Bargen.
:license: BSD 3-clause
"""

def align(argument):
    """Conversion function for the "align" option."""
    return directives.choice(argument, ('left', 'center', 'right'))


class IframeVideo(Directive):
    has_content = False
    required_arguments = 1
    optional_arguments = 0
    final_argument_whitespace = False
    option_spec = {
        'height': directives.nonnegative_int,
        'width': directives.nonnegative_int,
        'align': align,
    }
    default_width = 500
    default_height = 281

    def run(self):
        self.options['video_id'] = directives.uri(self.arguments[0])
        if not self.options.get('width'):
            self.options['width'] = self.default_width
        if not self.options.get('height'):
            self.options['height'] = self.default_height
        if not self.options.get('align'):
            self.options['align'] = 'left'
        return [nodes.raw('', self.html % self.options, format='html')]


class Youtube(IframeVideo):
    html = '<iframe src="http://www.youtube.com/embed/%(video_id)s" \
    width="%(width)u" height="%(height)u" frameborder="0" \
    webkitAllowFullScreen mozallowfullscreen allowfullscreen \
    class="align-%(align)s"></iframe>'


class Vimeo(IframeVideo):
    html = '<iframe src="http://player.vimeo.com/video/%(video_id)s" \
    width="%(width)u" height="%(height)u" frameborder="0" \
    webkitAllowFullScreen mozallowfullscreen allowFullScreen \
    class="align-%(align)s"></iframe>'


class Authornote(Directive):
    """
    Render author notes.
    """
    has_content = True
    required_arguments = 1
    final_argument_whitespace = True
    node_class = nodes.decoration
    def run(self):
        # Raise an error if the directive does not have contents.
        #self.assert_has_content()
        text = '\n'.join(self.content)
        # Make a node with the content
        content_node = self.node_class(rawsource=text)
        # Parse the directive contents into the new node.
        self.state.nested_parse(
            self.content,
            self.content_offset,
            content_node
        )
        # Create a new node with the prefix marker text for
        # Drupal custom filter to find.
        # Can apply permissions checks and other things on the
        # server side.
        prefix_text = '[[[cycoauthornote:' + self.arguments[0] + '|||\n'
        prefix_node = nodes.raw('', prefix_text, format='html')
        # Create a new node with the postfix marker text for
        # Cyco to find.
        postfix_text = ']]]\n'
        postfix_node = nodes.raw('', postfix_text, format='html')
        # Return the nodes in sequence.
        return [prefix_node, content_node, postfix_node]


class Exercise(Directive):
    has_content = False
    required_arguments = 1

    def run(self):
        # Put in pattern that is replaced in Drupal by a custom filter.
        # Can apply permissions checks and other things on the
        # server side.
        result = '[[[cycoexercise:' + self.arguments[0] + ']]]\n'
        raw_node = nodes.raw('', result, format='html')
        return [raw_node]


class Pseudent(Directive):
    has_content = True
    required_arguments = 1
    #
    node_class = nodes.decoration

    def run(self):
        # Raise an error if the directive does not have contents.
        #self.assert_has_content()
        text = '\n'.join(self.content)
        # Make a node with the content
        content_node = self.node_class(rawsource=text)
        # Parse the directive contents into the new node.
        self.state.nested_parse(
            self.content,
            self.content_offset,
            content_node
        )
        # Create a new node with the prefix marker text for
        # Drupal custom filter to find.
        # Can apply permissions checks and other things on the
        # server side.
        prefix_text = '[[[cycopseudent:' + self.arguments[0] + '|||'
        prefix_node = nodes.raw('', prefix_text, format='html')
        # Create a new node with the postfix marker text for
        # Cyco to find.
        postfix_text = ']]]'
        postfix_node = nodes.raw('', postfix_text, format='html')
        # Return the nodes in sequence.
        return [prefix_node, content_node, postfix_node]

class Pattern(Directive):
    has_content = False
    required_arguments = 1

    def run(self):
        # Put in pattern that is replaced in Drupal by a custom filter.
        # Can apply permissions checks and other things on the
        # server side.
        result = '[[[cycopattern:' + self.arguments[0] + ']]]\n'
        raw_node = nodes.raw('', result, format='html')
        return [raw_node]

#Register the new directives.
directives.register_directive('exercise', Exercise)
directives.register_directive('pseudent', Pseudent)
directives.register_directive('authornote', Authornote)
directives.register_directive('pattern', Pattern)
directives.register_directive('youtube', Youtube)
directives.register_directive('vimeo', Vimeo)

##Create a new directive
#class Swear(Directive):
#
#    has_content = True
#
#    def run(self):
#        self.assert_has_content()
#        if cyco_user.can_swear:
#            target = ''.join(self.content.data)
#            text = '<p>FUCK ' + target.upper() + '</p>'
#        else:
#            text = '<p>You are not allowed to swear, fuckhead.</p>'
#        return [nodes.raw('', text, format='html')]
#
##Register the new directive.
#directives.register_directive('swear', Swear)

#Read the content to translate.
testing = False
if testing:
    f = open('in_math.txt')
    content = f.readlines()
    f.close()
    data_in = ''.join(content)
else:
    data_in = ''
    for line in sys.stdin:
        data_in += line

#Parse some content.
#Use settings in docutils.conf.
#overrides = {'output_encoding': 'utf-8', 'output_encoding': 'latin-1'}
#overrides = {'math_output': 'MathJax'}
#doc = core.publish_parts(data_in, writer_name='html4css1', 
#  settings_overrides=overrides)['html_body']
doc = core.publish_parts(data_in, writer_name='html4css1')['html_body']
print (doc)
