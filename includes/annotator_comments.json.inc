<?php

/**
 * @file
 *
 * Annotator Storage JSON Endpoints.
 */

/**
 * Annotator Storage Root endpoint.
 */
function annotator_comments_storage_root($node) {
  $version = array(
    'name' => 'Annotator Store API',
    'version' => '2.0.0',
  );

  drupal_json_output((object) $version);
}

/**
 * Annotator Storage List endpoint.
 */
function annotator_comments_storage_annotations($node) {
  switch ($_SERVER['REQUEST_METHOD']) {
    case 'GET':
      $annotations = annotator_comments_get_annotations($node);
      drupal_json_output($annotations);

      break;

    case 'POST':
      $annotation = file_get_contents("php://input");
      $annotation = json_decode($annotation, TRUE);

      $comment = annotator_comments_save_annotation($annotation);

      drupal_add_http_header('Status', '303 SEE OTHER');
      drupal_add_http_header('Location', url('ajax/annotator-comments/' . $node->nid . '/annotations/' . $comment->cid, array('absolute' => TRUE)));

      break;
  }
}

/**
 * Annotator Storage Annotation endpoint.
 */
function annotator_comments_storage_annotation($node, $id) {
  switch ($_SERVER['REQUEST_METHOD']) {
    case 'GET':
      $annotation = annotator_comments_get_annotation($id);
      drupal_json_output($annotation);
      break;

    case 'PUT':
      $annotation = file_get_contents("php://input");
      $annotation = json_decode($annotation, TRUE);
      annotator_comments_update_annotation($annotation);

      drupal_add_http_header('Status', '303 SEE OTHER');
      drupal_add_http_header('Location', url('ajax/annotator-comments/' . $node->nid . '/annotations/' . $annotation['id'], array('absolute' => TRUE)));

      break;

    case 'DELETE':
      annotator_comments_delete_annotation($id);
      drupal_add_http_header('Status', '204 NO CONTENT');
      drupal_add_http_header('Content-Length', '0');

      break;
  }
}
