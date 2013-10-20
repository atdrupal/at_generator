<?php
/**
 * @file atg.drush.inc
 */

function atg_drush_command() {
  $commands[] = array();

  $commands['atg-module'] = array(
    'description' => 'Generate new module',
    'arguments' => array(
      'name' => 'Module name',
    ),
    'options' => array(
      'description'   => 'Description for module',
      'version'       => 'Default is 8.x-1.0-dev',
      'dependencies'  => '…',
      'readme'        => 'TRUE',
      'hooks'         => 'permission,install,form_alter',
    ),
    'examples' => array(
      'drush agt:module my_module --description="…" --version="8.x-1.0-dev" --dependencies=node,user --hooks=permissions,install,uninstall'
    ),
    'aliases' => array('atg:module', 'atgm'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  return $commands;
}

/**
 * Callback for atg-module command.
 */
function drush_atg_module($name) {
  $description = drush_get_option('description', "Description for module {$name}");
  $version = drush_get_option('version', '8.x-1.0-dev');
  $dependencies = drush_get_option('dependencies', '');
  $readme = drush_get_option('readme', TRUE);
  $hooks = drush_get_option('hooks', '');

  drush_print_r(array(
    $name, $description, $version, $dependencies, $readme, $hooks
  ));
}

class GeneratorCommand {
    private $generator;

    // only useful for unit tests
    public function setGenerator(Generator $generator)
    {
        $this->generator = $generator;
    }

    protected abstract function createGenerator();

    protected function getGenerator(BundleInterface $bundle = null) {
      if (null === $this->generator) {
        $this->generator = $this->createGenerator();
        $this->generator->setSkeletonDirs($this->getSkeletonDirs($bundle));
      }

      return $this->generator;
    }
}
