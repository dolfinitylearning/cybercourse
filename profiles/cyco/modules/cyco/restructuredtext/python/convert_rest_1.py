import sys
from docutils import nodes, core, io
from docutils.parsers.rst import Directive, directives
from docutils.parsers.rst.roles import set_classes
from docutils.utils.code_analyzer import Lexer, LexerError, NumberLines

#class Pseudent(BasePseudoSection):
#
#    node_class = nodes.sidebar
#
#    option_spec = BasePseudoSection.option_spec.copy()
#    option_spec['subtitle'] = directives.unchanged_required
#
#    def run(self):
#        if isinstance(self.state_machine.node, nodes.sidebar):
#            raise self.error('The "%s" directive may not be used within a '
#                             'sidebar element.' % self.name)
#        return BasePseudoSection.run(self)
#
##Register the new directive.
#directives.register_directive('pseudent', Pseudent)

##Class representing a CyCo user with certain permissions.
#class CyCoUser:
#    #Permission
#    can_swear = False
#    def set_can_swear(self, can_swear_in):
#      self.can_swear = ( can_swear_in == 'can_swear' )
#

class Exercise(Directive):
    """
    reStructuredText directive to show code listings with google-code-prettify
    """
    has_content = False
    required_arguments = 1

    def run(self):
        result = '[[[cycoexercise ' + self.arguments[0] + ']]]\n'
        raw_node = nodes.raw('', result, format='html')
        return [raw_node]


#class Pseudent(Directive):
#    has_content = True
#    required_arguments = 1

#    def run(self):
#        # Raise an error if the directive does not have contents.
#        self.assert_has_content()
#        text = '\n'.join(self.content)
#        text ='[[[pseudent ' + self.arguments[0] + '|||' + text + ']]]'
#        # Create node, to be populated by `nested_parse`.
#        contents_node = self.node_class(rawsource=text)
#        # Parse the directive contents.
#        self.state.nested_parse(self.content, self.content_offset,
#                                contents_node)
#        return [contents_node]

#Register the new directives.
directives.register_directive('exercise', Exercise)
#directives.register_directive('pseudent', Pseudent)


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
#
##Create a user.
#cyco_user = CyCoUser()
#
##Read user permisssions from PHP.
#can_swear = input()
#cyco_user.set_can_swear(can_swear)

#Read the content to translate.
data_in = ''
for line in sys.stdin:
    data_in += line

#Parse some content.
doc = core.publish_parts(data_in, writer_name='html')['html_body']
print (doc)
