<?php

/**
 * @file
 * Utility functions...
 */

/**
 * Get the parent for the given object, for which to create an AIP.
 *
 * @param AbstractObject $object
 *
 * @return string|FALSE
 *   The first eligible parent's PID, or FALSE if we couldn't find any.
 */
function archidora_get_parent(AbstractObject $object) {
  $map = function ($relationship) {
    return $relationship['object']['value'];
  }

  $rels = array(
    FEDORA_RELS_EXT_URI => array(
      'isMemberOfCollection',
      'isMemberOf',
    ),
  );
  $memberships = array();
  foreach ($rels as $uri => $preds) {
    foreach ($preds as $pred) {
      $parent_pids = array_map($map, $object->get($uri, $pred));
      $memberships = array_merge($memberships, $parent_pids);
    }
  }

  return reset($memberships);
}