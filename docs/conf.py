project = 'planet-incremental'
copyright = '2023, Pawel Szajna'
author = 'Pawel Szajna'

extensions = ['breathe']
breathe_default_project = 'planet-incremental'

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

html_theme = 'furo'
html_static_path = ['_static']

latex_elements = {
    'papersize': 'b5paper',
    'pointsize': '11pt',
}
