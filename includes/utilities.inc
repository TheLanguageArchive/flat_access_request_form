<?php
/**
 * Check whether to show link
 *
 * @return boolean
 */
function flat_access_request_form_is_form_available(AbstractObject $object) {

    if (true === flat_access_request_form_excluded_object($object)) {

        // object is excluded, don't show link
        return false;
    }

    if (false === flat_access_request_form_check_roles()) {

        // user is not allowed to see form
        return false;
    }

    $facets = flat_access_request_form_get_facet_access_levels($object->id);

    if (null === $facets) {

        // facets not available
        // fetching access levels of the children
        $children = flat_access_request_form_get_children_access_levels($object->id);

        if (in_array(AccessLevel::ROLE_SPECIFIC, $children)) {
            return true;
        }

        if (in_array(AccessLevel::ROLE_ACADEMIC, $children)) {
            return flat_access_request_form_is_user_academic();
        }

    } else {

        // facets available
        if (in_array(AccessLevelFacet::FACET_BUCKET_RESTRICTED, $facets)) {
            return true;
        }

        if (in_array(AccessLevelFacet::FACET_BUCKET_ACADEMIC, $facets)) {
            return flat_access_request_form_is_user_academic();
        }
    }

    return false;
}

/**
 * Getting children access levels
 *
 * @param string $pid
 * @return array
 */
function flat_access_request_form_get_children_access_levels($pid) {

    module_load_include('inc', 'flat_access_level_display', 'includes/backend');

    $data   = flat_access_level_display_compound_object_query($pid);
    $levels = [];

    foreach ($data as $child) {

        foreach ($child['roles'] as $role) {
            $levels[] = $role;
        }
    }

    return array_unique($levels);
}

/**
 * Get facet access levels
 *
 * @return array
 */
function flat_access_request_form_get_facet_access_levels()
{
    global $_islandora_solr_queryclass;

    if (null === $_islandora_solr_queryclass || !isset($_islandora_solr_queryclass->islandoraSolrResult['facet_counts'])) {
        return null;
    }

    $facets = $_islandora_solr_queryclass->islandoraSolrResult;
    return array_keys($facets['facet_counts']['facet_fields'][AccessLevelFacet::FACET_FIELD]);
}

/**
 * Check whether user has an academic role
 *
 * @return boolean
 */
function flat_access_request_form_is_user_academic() {

    global $user;
    return in_array(AccessLevel::ROLE_ACADEMIC, $user->roles);
}
